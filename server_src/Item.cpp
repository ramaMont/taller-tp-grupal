#include "Item.h"
#include "Player.h"
#include <ConfigVariable.h>


Item::Item(Coordinates p): Posicionable(p) { 
	atravesable(true);
}

Coordinates& Item::getPosition(){
	return posicion;
}

void Item::setPosition(Coordinates& position){
	posicion = position;
}


bool Food::use(Player* player){
	return player->addHealth((int)configs[CONFIG::puntos_comida]);
}

bool Medicine::use(Player* player){
	return player->addHealth((int)configs[CONFIG::puntos_kit]);
}

bool Blood::use(Player* player){
	if (player->lowHealth()){
		player->addHealth(1);
		return true;
	}
	return false;
}


Bullets::Bullets(Coordinates p): Item(p){
	this->cantidad = (int)configs[CONFIG::cantidad_balas];
}

Bullets::Bullets(Coordinates p, int cant): Item(p){
	this->cantidad = cant;
}

bool Bullets::use(Player* player){
	return player->addBullets(this->cantidad);
}


bool Key::use(Player* player){
	return player->addKey();
}


bool MachineGun::use(Player* player){
	return player->addGun(GunNumber::MACHINE_GUN);
}

bool FireCanon::use(Player* player){
	return player->addGun(GunNumber::CANON_GUN);
}

bool RocketLauncher::use(Player* player){
	return player->addGun(GunNumber::ROCKET_GUN);
}


Treasure::Treasure(int score, Coordinates p): Item(p), score(score){
}

bool Treasure::use(Player* player){
	player->addScore(score);
	return true;
}

Cross::Cross(Coordinates p): Treasure((int)configs[CONFIG::puntos_cruz], p){
}

Trophie::Trophie(Coordinates p): Treasure((int)configs[CONFIG::puntos_copa], p){
}

Chest::Chest(Coordinates p): Treasure((int)configs[CONFIG::puntos_cofre], p){
}

Crown::Crown(Coordinates p): Treasure((int)configs[CONFIG::puntos_corona], p){
}

