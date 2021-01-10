#include "Event.h"
#include "ParamReaderServer.h"
#include <chrono>
#include <cmath>

#define WALL_TIME_TO_MOVE 1000
#define WALL_STEP 0.15
#define ROCKET_TIME_TO_MOVE 1000
#define ROCKET_STEP 0.15
#define STEP 1

Event::Event(){
    _time = time(0);
    _finished = false;
}

bool Event::finished(){
    return _finished;
}

Event::~Event(){
}


DoorEvent::DoorEvent(Puerta* puerta): 
    Event(), door(puerta){
}

void DoorEvent::process(){ 
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


WallEvent::WallEvent(Coordinates position, Coordinates dir, 
    ParedFalsa* pared, Mapa& mapa):
    Event(), position(position), direction(dir),
    object(pared), mapa(mapa){
    direction.x = round(direction.x);
    direction.y = round(direction.y);
}

void WallEvent::process(){ 
    time_t time_now = time(0);
    double seconds = difftime(time_now, _time);
    if (seconds * 1000 < WALL_TIME_TO_MOVE)
        return;
    _time = time_now;
    move();
    // protocol mover pared
}

void WallEvent::move(){
    Coordinates aux = position;
    position.increment_on_direction(direction, WALL_STEP);
    if (mapa.hayObstaculoEn(position)){
        _finished = true;
        return;
    }
    if (aux != position){ 
        mapa.sacarPosicionable(aux);
        mapa.agregarPosicionable(object, position);
    }
}

WallEvent::~WallEvent(){
}


RocketEvent::RocketEvent(Coordinates position, Coordinates dir,
    Player* player, std::map<int, Player*>& enemigos):
    Event(), position(position), direction(dir),
    player(player), enemigos(enemigos),
    mapa(player->getMapa()){
    object = new Objeto(position);
    mapa.agregarPosicionable(object, position);
}

void RocketEvent::process(){
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


