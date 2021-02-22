#include "Object.h"

#include <ConfigVariable.h>
class ServerMap;
#include "ServerMap.h"
#include "ThGameModelServer.h"

#include <iostream>
#include <map>

#define STEP 1
#define DECIMALS 100

// Passage

Passage::Passage(Coordinates coordinates): Object(coordinates) {
    posicion.x += 0.5;  // Para estar en el centro de la posicion
    posicion.y += 0.5;  // Para estar en el centro de la posicion
}

bool Passage::open(Player *player){
    double angle = player->getPosicion().calculate_angle(
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
    double angle = player->getPosicion().calculate_angle(
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
    BlockingQueue<Protocol>& game_model, int id):
    Object(position), direction(dir), player(player), enemies(enemies),
    map(player->getMap()), game_model(game_model), id(id){
    exploded = false;
    Coordinates new_pos = posicion;
    while (posicion == new_pos){
        new_pos.increment_on_direction(direction, 0.5);
    }
    try {
        map.addPosicionable(this, new_pos);
    } catch(...) {
        explode(false);
        return;
    }
    posicion = new_pos;
    Protocol protocol(Protocol::action::ROCKET, player->getId(), id);
    game_model.push(protocol);
}

bool Rocket::move(){
    Coordinates new_position = posicion;
    new_position.increment_on_direction(direction, ROCKET_STEP);
    if ((posicion != new_position) && 
        (map.obstacleIn(new_position) || map.playerIn(new_position))){
        explode(true);
        return true;
    }
    if (posicion != new_position){
        map.removePosicionable(posicion);
        map.addPosicionable(this, new_position);
    }
    Protocol p(Protocol::action::MOVE_ROCKET, 0, id);
    game_model.push(p);
    posicion = new_position;
    return false;
}

void Rocket::explode(bool remove){
    if (exploded)
        return;
    if (remove){
        //map.removePosicionable(posicion);
        Protocol protocol(Protocol::action::EXPLOSION, 0, id);
        game_model.push(protocol);
    }
    hurtEnemies();
    exploded = true;
}

void Rocket::hurtEnemies(){
    for (auto it = enemies.begin(); it != enemies.end(); ++it){
        auto* enemy = it->second;
        double distance = posicion.calculate_distance(enemy->getPosicion());

        if (distance > (int)configs[CONFIG::distancia_explosion_cohete])
            continue;
        if (distance > 1 && crashes(posicion, enemy->getPosicion())){
            continue;
        }
			
        float damage = (int)configs[CONFIG::maximo_danio] * 
        (1 - distance /(int)configs[CONFIG::distancia_explosion_cohete]);
        
        bool is_dead = enemy->hurt(std::ceil(damage));
        if (is_dead)
            player->addKilledEnemy();
    }
}

bool Rocket::hasExploded(){
    return exploded;
}

int Rocket::getId(){
    return id;
}

bool Rocket::crashes(const Coordinates& start, const Coordinates& end){
	if (start == end) return false;
	Coordinates direction(end.x - start.x, end.y - start.y);
	Coordinates actual(start.x, start.y);
	direction.normalice_direction();
	actual.increment_on_direction(direction, STEP);

	while (actual != end){
		if (map.obstacleIn(actual) && actual != start)
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
