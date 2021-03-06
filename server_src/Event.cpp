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
    rocket_dir(rocket->getDirection()), rocket_id(rocket->getId()), 
    _exploded(false){
    rocket->setExploded(&_exploded);
    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    _time = (time_now.tv_usec / 1000);
}

void RocketEvent::process(BlockingQueue<Protocol>& game_model_queue){
    if (_exploded){
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
    Protocol protocol(Protocol::action::ROCKET_TIME, 0, rocket_id);   
    game_model_queue.push(protocol);
    rocket_pos.increment_on_direction(rocket_dir, ROCKET_STEP);
}

RocketEvent::~RocketEvent(){
}
