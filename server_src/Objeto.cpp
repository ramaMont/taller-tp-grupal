#include "Objeto.h"

#include <ConfigVariable.h>
class Mapa;
#include "Mapa.h"
#include "ThGameModelServer.h"
#include <iostream>

#define STEP 1

// Passage

Passage::Passage(Coordinates coordinates): Object(coordinates) {
    posicion.x += 0.5;  // Para estar en el centro de la posicion
    posicion.y += 0.5;  // Para estar en el centro de la posicion
}

bool Passage::open(Player *player){
    double angle = player->get_coordinates().calculate_angle(
        player->get_direction(), posicion);
    return (angle < 1);
}


// Door

Door::Door(Coordinates coordinates): Object(coordinates), reopen(false){
    posicion.x += 0.5;  // Para estar en el centro de la posicion
    posicion.y += 0.5;  // Para estar en el centro de la posicion
    has_event = false;
}

bool Door::open(Player *player){
    return openDoor(player);
}

bool Door::openDoor(Player *player){
    double angle = player->get_coordinates().calculate_angle(
        player->get_direction(), posicion);
    if (angle > 1)
        return false;
    bool had_event = has_event;
    has_event = true;
    reopen = true;
    return !had_event;
}

void Door::close(){
	atravesable(false);
	has_event = false;
}

void Door::letPass(){
    atravesable(true);
    reopen = true;
}

std::atomic<bool>& Door::getReopen(){
    return reopen;
}

bool KeyDoor::open(Player *player){
	if (opened || player->useKey()){
        opened = true;
		return openDoor(player);
    }
    return false;
}
	
    
// Rocket

Rocket::Rocket(Coordinates position, Coordinates dir,
    Player* player, std::map<int, Player*>& enemies,
    ThGameModelServer& game_model):
    Object(position), direction(dir), player(player), enemies(enemies),
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
        double distance = posicion.calculate_distance(
			enemy->get_coordinates());

        if (distance > (int)configs[CONFIG::distancia_explosion_cohete])
            continue;
        if (crashes(posicion, enemy->get_coordinates()))
            continue;
			
        float damage = (int)configs[CONFIG::maximo_danio] * 
        (1 - distance /(int)configs[CONFIG::distancia_explosion_cohete]);
        bool is_dead = enemy->recibirDanio(std::ceil(damage));
        if (is_dead)
            player->agregarEnemigoMuerto();
    }
    exploded = true;
}

bool Rocket::hasExploded(){
    return exploded;
}

bool Rocket::crashes(const Coordinates& start, const Coordinates& end){
	if (start == end) return false;
	Coordinates direction(end.x - start.x, end.y - start.y);
	Coordinates actual(start.x, start.y);
	direction.normalice_direction();
	actual.increment_on_direction(direction, STEP);

	while (actual != fin){
		if (map.hayObstaculoEn(actual) && actual != start)
			return true;
		actual.increment_on_direction(direction, STEP);
	}
	return false;
}

Coordinates Rocket::getDirection(){
    return direction;
}

Rocket::~Rocket(){
}	
