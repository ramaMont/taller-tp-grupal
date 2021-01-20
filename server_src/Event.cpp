#include "Event.h"
#include <ConfigVariable.h>
#include <chrono>
#include <cmath>
#include <iostream>
#include "ThGameEvents.h"
#include <Protocol.h>

#define WALL_TIME_TO_MOVE 1000
#define WALL_STEP 0.15
#define ROCKET_TIME_TO_MOVE 1000
#define ROCKET_STEP 0.15
#define STEP 1
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
    Event(), player(player), map(map), th_game_events(game_e){
}

void OpenEvent::process(ThGameModelServer& game_model){
    Coordinates pos = player->get_coordinates();
    pos.increment_on_direction(player->get_direction(), 1);
    Posicionable* p = map.obtenerPosicionableEn(pos);
    if (p && typeid(p) == typeid(Puerta)){
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
    if (p && typeid(p) == typeid(ParedFalsa)){
        ParedFalsa* wall = static_cast<ParedFalsa*>(p);
        if (wall->abrir(player)){
            // Protocol sacar pared
        }
    }   
}

OpenEvent::~OpenEvent(){
}


// Finish Game
FinishGameEvent::FinishGameEvent(std::map<int, Player*>& players):
    Event(), players(players){
}

void FinishGameEvent::process(BlockingQueue<Protocol>& game_model_queue){
    time_t time_now = time(0);
    double seconds = difftime(time_now, _time);

    if (seconds/MINUTE_SECONDS > configs[CONFIG::minutos_partida]
        || someoneWon()){
        // Protocol finish
        _finished = true;
    }
}

bool FinishGameEvent::someoneWon(){
    bool winner = false;
    for (auto it = players.begin(); it != players.end(); ++it){
        if (it->second->estaVivo()){
            if (winner)
                return false;
            winner = true;
        }
    }
    return true;
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
RocketEvent::RocketEvent(Coordinates position, Coordinates dir,
    Player* player, std::map<int, Player*>& enemigos):
    Event(), position(position), direction(dir),
    player(player), enemigos(enemigos),
    mapa(player->getMapa()){
    object = new Objeto(position);
    mapa.agregarPosicionable(object, position);
}

void RocketEvent::process(BlockingQueue<Protocol>& game_model_queue){
    time_t time_now = time(0);
    double seconds = difftime(time_now, _time);
    if (seconds * 1000 < ROCKET_TIME_TO_MOVE)
        return;
    _time = time_now;
    move();
    // Protocol mover rocket
}

void RocketEvent::move(){
    mapa.sacarPosicionable(position);
    position.increment_on_direction(direction, ROCKET_STEP);
    if (mapa.hayObstaculoEn(position)){
        delete(object);
        return explote();
    }
    mapa.agregarPosicionable(object, position);
}

void RocketEvent::explote(){
    for (auto it = enemigos.begin(); it != enemigos.end(); ++it){
        auto* enemigo = it->second;
        double distancia = position.calculate_distance(
			enemigo->get_coordinates());

        if (distancia > (int)configs[CONFIG::distancia_explosion_cohete])
            continue;
        if (colisionaConObjeto(position, enemigo->get_coordinates()))
            continue;
			
        float damage = (int)configs[CONFIG::maximo_danio] * 
        (1 - distancia /(int)configs[CONFIG::distancia_explosion_cohete]);
        bool is_dead = enemigo->recibirDanio(std::ceil(damage));
        if (is_dead)
            player->agregarEnemigoMuerto();
    }
    _finished = true;
}

bool RocketEvent::colisionaConObjeto(const Coordinates& inicio, 
    const Coordinates& fin){
	if (inicio == fin) return false;
	Coordinates direccion(fin.x - inicio.x, fin.y - inicio.y);
	Coordinates actual(inicio.x, inicio.y);
	direccion.normalice_direction();
	actual.increment_on_direction(direccion, STEP);

	while (actual != fin){
		if (mapa.hayObstaculoEn(actual) && actual != inicio)
			return true;
		actual.increment_on_direction(direccion, STEP);
	}
	return false;
}

RocketEvent::~RocketEvent(){
}


