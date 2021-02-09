#include "Event.h"
#include <ConfigVariable.h>
#include <chrono>
#include <cmath>
#include <iostream> //
#include <sys/time.h>
#include "ThGameEvents.h"
#include "ThGameModelServer.h"
#include <Protocol.h>

#define ROCKET_TIME_TO_MOVE 100
#define MINUTE_SECONDS 60

Event::Event(){
    _time = time(0);
    _finished = false;
}

bool Event::finished(){
    return _finished;
}

Event::~Event(){
}


// Open 
OpenEvent::OpenEvent(Player* player, Mapa& map, ThGameEvents& game_e):
    player(player), map(map), th_game_events(game_e){
}

void OpenEvent::process(ThGameModelServer& game_model){
    Coordinates pos = player->getPosicion();
    Object* p = map.getNearestPassage(pos);
    if (p && typeid(*p) == typeid(Door)){
        Door* puerta = static_cast<Door*>(p);
        if (puerta->open(player)){
            Event* doorE = new DoorOpeningEvent(puerta);
            th_game_events.add(doorE);

            Coordinates door_pos = puerta->get_position();
            Protocol protocol(Protocol::action::OPENING, player->getId(),
                Protocol::direction::STAY, 0, door_pos.x, door_pos.y);
            game_model.echoProtocol(protocol);
        }
    }
    if (p && typeid(*p) == typeid(Passage)){
        Passage* wall = static_cast<Passage*>(p);
        if (wall->open(player)){
            Coordinates position = wall->getPosicion();
            Protocol protocol(Protocol::action::OPEN_PASSAGE, player->getId(),
            Protocol::direction::STAY, 0, position.x, position.y);    
            game_model.echoProtocol(protocol);
            map.removePassage(position);
        }
    }
}

OpenEvent::~OpenEvent(){
}


// Finish Game
FinishGameEvent::FinishGameEvent():
    Event(){
}

void FinishGameEvent::process(BlockingQueue<Protocol>& game_model_queue){
    time_t time_now = time(0);
    double seconds = difftime(time_now, _time);

    if (seconds/MINUTE_SECONDS > configs[CONFIG::minutos_partida]){
        Protocol protocol;
		protocol.setAction(Protocol::action::ENDGAME);
		game_model_queue.push(protocol);
        _finished = true;
    }
}

FinishGameEvent::~FinishGameEvent(){
}

// Opening Door
DoorOpeningEvent::DoorOpeningEvent(Door *door):
    Event(), door(door){
    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    _time = (time_now.tv_usec / 1000);
}

void DoorOpeningEvent::process(BlockingQueue<Protocol>& game_model_queue){
    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    time_t new_time = (time_now.tv_usec / 1000);
    time_t diff = new_time - _time;
    if (diff < 0)
        diff += 1000;
    if (diff > 600){
        Coordinates door_pos = door->get_position();
        Protocol protocol(Protocol::action::OPENING, 0,
            Protocol::direction::STAY, 0, door_pos.x, door_pos.y);    

        game_model_queue.push(protocol);
        _finished = true;
    }
}

DoorOpeningEvent::~DoorOpeningEvent(){
}


// Door 
DoorEvent::DoorEvent(Door* door): 
    Event(), door(door), reopen(door->getReopen()){
    door->letPass();
}

void DoorEvent::process(BlockingQueue<Protocol>& game_model_queue){ 
    if (reopen){
        _time = time(0);
        reopen = false;
        return;
    }
    time_t time_now = time(0);
    double seconds = difftime(time_now, _time);
    if (seconds > configs[CONFIG::segundos_cerrar_puerta]){
        // Protocol, usar pos para mandarle en el protocolo la posicion de la puerta.
        Coordinates door_pos = door->get_position();
        Protocol protocol(Protocol::action::CLOSE, 0,
            Protocol::direction::STAY, 0, door_pos.x, door_pos.y);   
        game_model_queue.push(protocol);
        _finished = true;
    }
}

DoorEvent::~DoorEvent(){
}


// Rocket
RocketEvent::RocketEvent(Rocket* rocket):
    Event(), rocket(rocket), rocket_pos(rocket->getPosicion()),
    rocket_dir(rocket->getDirection()){
    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    _time = (time_now.tv_usec / 1000);
}

void RocketEvent::process(BlockingQueue<Protocol>& game_model_queue){
    if (rocket->hasExploded()){
        delete(rocket);
        _finished = true;
        return;
    }
    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    time_t new_time = (time_now.tv_usec / 1000);
    time_t diff = new_time - _time;
    if (diff < 0)
        diff += 1000;
    if (diff < ROCKET_TIME_TO_MOVE)
        return;
    _time = (time_now.tv_usec / 1000);
    Protocol protocol(Protocol::action::ROCKET, 0,
        Protocol::direction::STAY, 0, rocket_pos.x, rocket_pos.y);   
    game_model_queue.push(protocol);
    rocket_pos.increment_on_direction(rocket_dir, ROCKET_STEP);
}

RocketEvent::~RocketEvent(){
}
