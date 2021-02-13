#include "Soldier.h"

#include "ExceptionServer.h"
#include "ServerMap.h"
#include "Player.h"
#include <ConfigVariable.h>

#include <unistd.h>
#include <typeinfo>
#include <thread>
#include <chrono>
#include <iostream>

#define GRADOS_180 180
#define PI 3.14159265358979323846
#define PASO 1
#define ROTACION_45 0.7071
#define PORCENTAJE 100
#define DISTANCIA_CUCHILLO 2

#define TEXTURE_MACHINE_GUN 6
#define TEXTURE_CANON_GUN 9
#define TEXTURE_ROCKET_GUN 4


// Soldier State

SoldierState::SoldierState(Player *player, int &bullets,
        BlockingQueue<Protocol>& game_model_queue): player(player),
    dog(bullets), guard(bullets), ss(bullets),
    officer(bullets), mutant(bullets), actual_gun(1),
    game_model_queue(game_model_queue){
	soldier = &guard;
	last_soldier = nullptr;
}

int SoldierState::actualGun(){
	return actual_gun;
}

bool SoldierState::addGun(int gun_number){
    switch (gun_number){
		case GunNumber::MACHINE_GUN:
			return ss.addGun();
		case GunNumber::CANON_GUN:
			return officer.addGun();
		case GunNumber::ROCKET_GUN:
			return mutant.addGun();
	}
	return false;
}

void SoldierState::switchGun(int gun_number){
	switch (gun_number){
		case GunNumber::KNIFE:
			soldier = &dog;
			break;
		case GunNumber::GUN:
			if (guard.ready())
				soldier = &guard;
			break;
		case GunNumber::MACHINE_GUN:
			if (ss.ready())
				soldier = &ss;
			break;
		case GunNumber::CANON_GUN:
			if (officer.ready())
				soldier = &officer;
			break;
		case GunNumber::ROCKET_GUN:
			if (mutant.ready())
				soldier = &mutant;
			break;
	}
    actual_gun = soldier->gunNumber();
}


int SoldierState::throwGun(const Coordinates& position){
    if (soldier == &guard){
        return 0;
    }
    last_soldier = &guard;
	return soldier->throwGun(player->getMap(), position);
}

int SoldierState::shoot(std::map<int, Player*>& enemies){
	int result = soldier->shoot(this->player, enemies);
	if (!soldier->ready()){
		last_soldier = soldier;
        Protocol protocol(player->getId(), GunNumber::KNIFE, 
            Protocol::action::SWITCH_GUN);
        game_model_queue.push(protocol);
	}
	return result;
}

void SoldierState::rechargeBullets(){
	if (last_soldier){
        Protocol protocol(player->getId(), last_soldier->gunNumber(), 
            Protocol::action::SWITCH_GUN);
        game_model_queue.push(protocol);
		last_soldier = nullptr;
	}
}


// Soldado

void Soldier::getCloserEnemies(std::map<int, Player*>& enemies,
    Player* player, std::set<std::pair<int, Player*>>& players){
    for (auto it = enemies.begin(); it != enemies.end(); ++it){
        auto enemy = it->second;
		if (enemy == player)
			continue;
		float angle = player->calculateAngle(enemy);
		int degrees = angle * GRADOS_180 / PI;
		if (degrees <= configs[CONFIG::rango_de_disparo])
		    players.insert(std::pair<int,Player*>(degrees, enemy));
	}
}

void Soldier::tryShoot(Player* player,  std::set<std::pair<int, Player*>>& enemies, float precision){
	for (std::pair<int, Player*> e: enemies){
		if (fireBullet(player, precision, e.first, e.second))
			return;
	}
}

bool Soldier::fireBullet(Player *player, float precision, int angle, Player* enemy){
	int n_rand = rand() % PORCENTAJE;
	if ((n_rand / PORCENTAJE) > precision)	// Falla el tiro
		return true;

	if (crashes(player->getMap(), player->getPosicion(), enemy->getPosicion()))   
	    return false;   // Hay un objeto en el medio   

    atack(player, enemy, precision, angle);
    return true;
}

bool Soldier::crashes(ServerMap& map, const Coordinates& start, const Coordinates& end){
	if (start == end) return false;
	Coordinates direction(std::floor(end.x) + 0.5 - start.x,
                        std::floor(end.y) + 0.5 - start.y);
	Coordinates actual(start.x, start.y);
	direction.normalice_direction();
	actual.increment_on_direction(direction, PASO);

	while (actual != end){
		if (map.obstacleIn(actual) && actual != start)
			return true;
		actual.increment_on_direction(direction, PASO);
	}
	return false;
}

void Soldier::atack(Player *player, Player* enemy, float precision, int angle){
	double distance = player->calculateDistance(enemy);

    float damage = precision - 
                  distance * configs[CONFIG::baja_precision_distancia];
	damage -= angle/(int)configs[CONFIG::rango_de_disparo];
	int n_rand = rand() % (int)configs[CONFIG::maximo_danio] + 1;
	damage *= n_rand;
	bool die = enemy->hurt(std::ceil(damage));
	if (die)
		player->addKilledEnemy();
}

bool Soldier::addGun(){
    bool had_gun = gun;
	gun = true;
	return !had_gun;
}


// Perro

Dog::Dog(int& n): Soldier(n){
}

int Dog::shoot(Player *player, std::map<int, Player*>& enemies){
	std::set<std::pair<int, Player*>> set_players;
	getCloserEnemies(enemies, player, set_players);
	bite(player, set_players);
	return 0;
}

void Dog::bite(Player *player, std::set<std::pair<int, Player*>>& enemies){
	for (std::pair<int, Player*> e: enemies){
		if (player->calculateDistance(e.second) < DISTANCIA_CUCHILLO){
			int damage = rand() % (int)configs[CONFIG::maximo_danio] + 1;
			bool die = e.second->hurt(damage);
			if (die)
				player->addKilledEnemy();
			return;
		}
	}
}

int Dog::throwGun(ServerMap& map, const Coordinates& position){
	return 0;
}

bool Dog::ready(){
	return true;
}

int Dog::gunNumber() const{
	return GunNumber::KNIFE;
}


// Guardia

Guard::Guard(int& bullets): Soldier(bullets){
}

int Guard::shoot(Player *player, std::map<int, Player*>& enemies){
	std::set<std::pair<int, Player*>> set_players;
	getCloserEnemies(enemies, player, set_players);
	tryShoot(player, set_players, configs[CONFIG::precision_pistola]);
	bullets --;
	return 0;
}

int Guard::throwGun(ServerMap& map, const Coordinates& position){
	return 0;
}

bool Guard::ready(){
	return bullets > 0;
}

int Guard::gunNumber() const{
	return GunNumber::GUN;
}


// SS

SS::SS(int &bullets): Soldier(bullets){
	gun = false;
}

int SS::shoot(Player *player, std::map<int, Player*>& enemies){
	std::set<std::pair<int, Player*>> set_players;
	getCloserEnemies(enemies, player, set_players);

	for (int i = 0; (i < configs[CONFIG::balas_rafaga_ametralladora]) 
	    && (bullets > 0); i++){
	    tryShoot(player, set_players, configs[CONFIG::precision_ametralladora]);
	    bullets --;
	}
	return 0;
}

int SS::throwGun(ServerMap& map, const Coordinates& position){
    Item* new_gun = new MachineGun(position);
    map.addItem(new_gun, position);
    gun = false;
    return TEXTURE_MACHINE_GUN;
}

bool SS::ready(){
	return bullets > 0 && gun;
}

int SS::gunNumber() const{
	return GunNumber::MACHINE_GUN;
}


// Oficial

Officer::Officer(int &bullets): Soldier(bullets){
	 gun = false;
}

int Officer::shoot(Player *player, std::map<int, Player*>& enemies){
	std::set<std::pair<int, Player*>> set_players;
	getCloserEnemies(enemies, player, set_players);
	tryShoot(player, set_players, configs[CONFIG::precision_canion]);
	bullets --;	
	return 0;
}

int Officer::throwGun(ServerMap& map, const Coordinates& position){
    Item* new_gun = new FireCanon(position);
    map.addItem(new_gun, position);
    gun = false;
    return TEXTURE_CANON_GUN;
}

bool Officer::ready(){
	return bullets > 0 && gun;
}

int Officer::gunNumber() const{
	return GunNumber::CANON_GUN;
}


// Mutante

Mutant::Mutant(int &bullets): Soldier(bullets){
    gun = false;
}

int Mutant::shoot(Player *player, std::map<int, Player*>& enemies){
	bullets -= (int)configs[CONFIG::balas_gastadas_lanzacohetes];
	return 1;
}

int Mutant::throwGun(ServerMap& map, const Coordinates& position){
    Item* new_gun = new RocketLauncher(position);
    map.addItem(new_gun, position);
    gun = false;
    return TEXTURE_ROCKET_GUN;
}

bool Mutant::ready(){
	return bullets > configs[CONFIG::balas_gastadas_lanzacohetes] && gun;
}

int Mutant::gunNumber() const{
	return GunNumber::ROCKET_GUN;
}

