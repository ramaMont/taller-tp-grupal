#include "Objeto.h"

#include <ConfigVariable.h>
class Mapa;
#include "Mapa.h"
#include "ThGameModelServer.h"
#include <iostream>

#define STEP 1


Coordinates& Objeto::getCoordinates(){
    return this->posicion;
}


ParedFalsa::ParedFalsa(Coordinates coordenadas): Objeto(coordenadas) {
    posicion.x += 0.5;  // Para estar en el centro de la posicion
    posicion.y += 0.5;  // Para estar en el centro de la posicion
}
bool ParedFalsa::abrir(Player *jugador){
    double angle = jugador->get_coordinates().calculate_angle(
        jugador->get_direction(), posicion);
    return (angle < 1);
}


Puerta::Puerta(Coordinates coordenadas): Objeto(coordenadas), reopen(false){
    posicion.x += 0.5;  // Para estar en el centro de la posicion
    posicion.y += 0.5;  // Para estar en el centro de la posicion
    has_event = false;
}



bool Puerta::abrir(Player *jugador){
    return abrirPuerta(jugador);
}

bool Puerta::abrirPuerta(Player *jugador){
    double angle = jugador->get_coordinates().calculate_angle(
        jugador->get_direction(), posicion);
    if (angle > 1)
        return false;
    bool had_event = has_event;
    has_event = true;
    reopen = true;
    return !had_event;
}

void Puerta::close(){
	atravesable(false);
	has_event = false;
}

void Puerta::letPass(){
    atravesable(true);
    reopen = true;
}

std::atomic<bool>& Puerta::getReopen(){
    return reopen;
}

bool PuertaCerrada::abrir(Player *jugador){
	if (this->llave || jugador->usarLlave())
		return abrirPuerta(jugador);
    return false;
}
	
    

Rocket::Rocket(Coordinates position, Coordinates dir,
    Player* player, std::map<int, Player*>& enemies,
    ThGameModelServer& game_model):
    Objeto(position), direction(dir), player(player), enemies(enemies),
    map(player->getMapa()){
    exploded = false;
    posicion.increment_on_direction(direction, 1.1);
    try {
        map.agregarPosicionable(this, posicion);
    } catch (...) {
        explode();
        return;
    }
    Protocol protocol(Protocol::action::ROCKET, 0, posicion.x, posicion.y);
    game_model.echoProtocol(protocol);
}

void Rocket::move(ThGameModelServer& game_model){
    map.sacarPosicionable(posicion);
    Protocol protocol(Protocol::action::MOVE_ROCKET, 0, posicion.x, posicion.y);
    game_model.echoProtocol(protocol);
    posicion.increment_on_direction(direction, ROCKET_STEP);
    if (map.hayObstaculoEn(posicion) || map.playerIn(posicion)){
        return explode();
    }
    map.agregarPosicionable(this, posicion);
    Protocol p(Protocol::action::ROCKET, 0, posicion.x, posicion.y);
    game_model.echoProtocol(p);
}

void Rocket::explode(){
    for (auto it = enemies.begin(); it != enemies.end(); ++it){
        auto* enemy = it->second;
        double distancia = posicion.calculate_distance(
			enemy->get_coordinates());

        if (distancia > (int)configs[CONFIG::distancia_explosion_cohete])
            continue;
        if (colisionaConObjeto(posicion, enemy->get_coordinates()))
            continue;
			
        float damage = (int)configs[CONFIG::maximo_danio] * 
        (1 - distancia /(int)configs[CONFIG::distancia_explosion_cohete]);
        bool is_dead = enemy->recibirDanio(std::ceil(damage));
        if (is_dead)
            player->agregarEnemigoMuerto();
    }
    exploded = true;
}

bool Rocket::hasExploded(){
    return exploded;
}

bool Rocket::colisionaConObjeto(const Coordinates& inicio, 
    const Coordinates& fin){
	if (inicio == fin) return false;
	Coordinates direccion(fin.x - inicio.x, fin.y - inicio.y);
	Coordinates actual(inicio.x, inicio.y);
	direccion.normalice_direction();
	actual.increment_on_direction(direccion, STEP);

	while (actual != fin){
		if (map.hayObstaculoEn(actual) && actual != inicio)
			return true;
		actual.increment_on_direction(direccion, STEP);
	}
	return false;
}

Coordinates Rocket::getDirection(){
    return direction;
}

Rocket::~Rocket(){
}	
