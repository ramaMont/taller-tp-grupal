#include "Event.h"
#include <ConfigVariable.h>
#include <chrono>
#include <cmath>
#include <iostream>
#include "ThGameEvents.h"
#include "ThGameModelServer.h"
#include <Protocol.h>

#define WALL_TIME_TO_MOVE 1000
#define WALL_STEP 0.15
#define ROCKET_TIME_TO_MOVE 1000
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
    Coordinates pos = player->get_coordinates();
    Objeto* p = map.getNearestDoor(pos);
    if (p && typeid(*p) == typeid(Puerta)){
        Puerta* puerta = static_cast<Puerta*>(p);
        if (puerta->abrir(player)){
            Event* doorE = new DoorEvent(puerta);
            th_game_events.add(doorE);
            // Protocol, usar pos para mandarle en el protocolo la posicion de la puerta.
            Protocol protocol;
            protocol.setAction(Protocol::action::OPEN);
            game_model.echoProtocol(protocol);
        }
    }
    if (p && typeid(*p) == typeid(ParedFalsa)){
        ParedFalsa* wall = static_cast<ParedFalsa*>(p);
        if (wall->abrir(player)){
            // Protocol sacar pared
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
        Protocol protocol(0);
		protocol.setAction(Protocol::action::ENDGAME);
		game_model_queue.push(protocol);
        _finished = true;
    }
}

FinishGameEvent::~FinishGameEvent(){
}


// Door 
DoorEvent::DoorEvent(Puerta* puerta): 
    Event(), door(puerta){
}

void DoorEvent::process(BlockingQueue<Protocol>& game_model_queue){ 
    time_t time_now = time(0);
    double seconds = difftime(time_now, _time);
    if (seconds >= configs[CONFIG::segundos_cerrar_puerta]){
        door->cerrar();
        // protocol cerrar puerta
        _finished = true;
    }
}

DoorEvent::~DoorEvent(){
}


// Rocket
RocketEvent::RocketEvent(Rocket* rocket):
    Event(), rocket(rocket){
}

void RocketEvent::process(BlockingQueue<Protocol>& game_model_queue){
    if (rocket->hasExploded()){
        delete(rocket);
        _finished = true;
        return;
    }
    time_t time_now = time(0);
    double seconds = difftime(time_now, _time);
    if (seconds * 1000 < ROCKET_TIME_TO_MOVE)
        return;
    _time = time_now;
    // Protocol mover rocket
}

RocketEvent::~RocketEvent(){
}


