#include "Soldado.h"

#include "Mapa.h"
#include <ConfigVariable.h>

#include <unistd.h>
#include <typeinfo>
#include <thread>
#include <chrono>
#include <iostream>
#include "ExceptionServer.h"
#define GRADOS_180 180
#define PI 3.14159265358979323846
#define PASO 1
#define ROTACION_45 0.7071
#define PORCENTAJE 100
#define DISTANCIA_CUCHILLO 2

// Soldier State

SoldierState::SoldierState(Player *player, int &bullets): player(player),
    dog(bullets), guard(bullets), ss(bullets),
    officer(bullets), mutant(bullets), actual_gun(1){
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
	this->actual_gun = soldier->actualGun();
}


int SoldierState::throwGun(){
	Soldier *s = soldier;
	soldier = &guard;
	return s->throwGun(this->player);
}

int SoldierState::shoot(std::map<int, Player*>& enemies){
	int fired_bullets = soldier->shoot(this->player, enemies);
	if (!soldier->ready()){
		last_soldier = soldier;
		soldier = &dog;
	}
	actual_gun = soldier->actualGun();
	return fired_bullets;
}

void SoldierState::rechargeBullets(){
	if (last_soldier){
		soldier = last_soldier;
		last_soldier = nullptr;
	}
	actual_gun = soldier->actualGun();
}


// Soldado

int radianesAGrados(double radianes){
	return radianes * GRADOS_180 / PI;
}

void Soldado::obtenerEnemigosCercanos(std::map<int, Player*>& enemigos,
    Player* player, std::set<std::pair<int, Player*>>& players){
    for (auto it = enemigos.begin(); it != enemigos.end(); ++it){
        auto enemigo = it->second;
		if (enemigo == player)
			continue;
		float angulo = player->calcularAngulo(enemigo);
		int grados = radianesAGrados(angulo);
		if (grados <= configs[CONFIG::rango_de_disparo])
		    players.insert(std::pair<int,Player*>(grados,enemigo));
	}
}

void Soldado::tryShoot(Player* player,  std::set<std::pair<int, Player*>>& enemigos, float precision){
	for (std::pair<int, Player*> e: enemigos){
		if (dispararBala(player, precision, e.first, e.second))
			return;
	}
}

bool Soldado::colisionaConObjeto(Mapa& mapa, const Coordinates& inicio, 
    const Coordinates& fin){
	if (inicio == fin) return false;
	Coordinates direction(std::floor(fin.x) + 0.5 - inicio.x,
                              std::floor(fin.y) + 0.5 - inicio.y);
	Coordinates actual(inicio.x, inicio.y);
	direction.normalice_direction();
	actual.increment_on_direction(direction, PASO);

	while (actual != fin){
		if (mapa.hayObstaculoEn(actual) && actual != inicio)
			return true;
		actual.increment_on_direction(direction, PASO);
	}
	return false;
}

void Soldado::atacar(Player *player, Player* enemigo, float precision, int angulo){
	double distancia = player->calcularDistancia(enemigo);

    float danio = precision - 
                  distancia * configs[CONFIG::baja_precision_distancia];
	danio -= angulo/(int)configs[CONFIG::rango_de_disparo];
	int n_rand = rand() % (int)configs[CONFIG::maximo_danio] + 1;
	danio *= n_rand;
	bool murio = enemigo->recibirDanio(std::ceil(danio));
	if (murio)
		player->agregarEnemigoMuerto();
}


bool Soldado::dispararBala(Player *player, float precision, int angulo, Player* enemigo){
	int n_rand = rand() % PORCENTAJE;
	if ((n_rand / PORCENTAJE) > precision)	// Falla el tiro
		return true;

	if (colisionaConObjeto(player->getMapa(), player->get_coordinates(),
	    enemigo->get_coordinates()))	// Hay un objeto en el medio       
	    return false;

    atacar(player, enemigo, precision, angulo);
    return true;
}


// Perro

Perro::Perro(int& n): Soldado(n){
}

int Perro::disparar(Player *player, std::map<int, Player*>& enemigos){
	std::set<std::pair<int, Player*>> set_players;
	obtenerEnemigosCercanos(enemigos, player, set_players);
	bite(player, set_players);
	return 0;
}

void Perro::bite(Player *player, angulos_enemigos_t& enemigos){
	for (std::pair<int, Player*> e: enemigos){
		if (player->calcularDistancia(e.second) < DISTANCIA_CUCHILLO){
			int danio = rand() % (int)configs[CONFIG::maximo_danio] + 1;
			bool murio = e.second->recibirDanio(danio);
			if (murio)
				player->agregarEnemigoMuerto();
			return;
		}
	}
}

int Perro::soltarArma(Player *player){
	return 0;
}

bool Perro::estaListo(){
	return true;
}

int Perro::numeroArma() const{
	return N_CUCHILLO;
}


// Guardia

Guardia::Guardia(int& balas): Soldado(balas){
}

int Guardia::disparar(Player *player, std::map<int, Player*>& enemigos){
	std::set<std::pair<int, Player*>> set_players;
	obtenerEnemigosCercanos(enemigos, player, set_players);
	tryShoot(player, set_players, configs[CONFIG::precision_pistola]);
	this->balas --;
	return 1;
}

int Guardia::soltarArma(Player *player){
	return 0;
}

bool Guardia::estaListo(){
	return this->balas > 0;
}

int Guardia::numeroArma() const{
	return N_PISTOLA;
}


// SS

SS::SS(int &balas): Soldado(balas){
	this->tieneArma = false;
}

bool SS::agregarArma(Ametralladora *ametr){
	if (this->tieneArma)
		return false;
	this->tieneArma = true;
	return true;
}

int SS::disparar(Player *player, std::map<int, Player*>& enemigos){
	std::set<std::pair<int, Player*>> set_players;
	obtenerEnemigosCercanos(enemigos, player, set_players);

	int balas_disparadas = 0;
	for (int i = 0; (i < configs[CONFIG::balas_rafaga_ametralladora]) 
	    && (this->balas > 0); i++){
	    tryShoot(player, set_players, configs[CONFIG::precision_ametralladora]);
	    this->balas --;
	    balas_disparadas ++;
	}
	return balas_disparadas;
}

int SS::soltarArma(Player *player){
    Mapa &mapa = player->getMapa();
    Item* arma = new Ametralladora(player->get_coordinates());
    mapa.agregarItem(arma, player->get_coordinates());
    this->tieneArma = false;
    return 6;
}

bool SS::estaListo(){
	return this->balas > 0 && this->tieneArma;
}

int SS::numeroArma() const{
	return N_AMETRALLADORA;
}


// Oficial

Oficial::Oficial(int &balas): Soldado(balas){
	 this->tieneArma = false;
}

bool Oficial::agregarArma(CanionDeCadena *canion){
	if (this->tieneArma)
		return false;
	this->tieneArma = true;
    return true;
}
	
int Oficial::disparar(Player *player, std::map<int, Player*>& enemigos){
	std::set<std::pair<int, Player*>> set_players;
	obtenerEnemigosCercanos(enemigos, player, set_players);
	tryShoot(player, set_players, configs[CONFIG::precision_canion]);
	this->balas --;	
	return 1;
}

int Oficial::soltarArma(Player *player){
    Mapa &mapa = player->getMapa();
    Item* arma = new CanionDeCadena(player->get_coordinates());
    mapa.agregarItem(arma, player->get_coordinates());
    this->tieneArma = false;
    return 9;
}

bool Oficial::estaListo(){
	return this->balas > 0 && this->tieneArma;
}

int Oficial::numeroArma() const{
	return N_CANION;
}


// Mutante

Mutante::Mutante(int &balas): Soldado(balas){
    this->tieneArma = false;
}

bool Mutante::agregarArma(Lanzacohetes *lanzacohetes){
	if (this->tieneArma)
		return false;
	this->tieneArma = true;
	return true;	
}

int Mutante::disparar(Player *player, std::map<int, Player*>& enemigos){
	throw RocketException();//
	this->balas -= (int)configs[CONFIG::balas_gastadas_lanzacohetes];
	return (int)configs[CONFIG::balas_gastadas_lanzacohetes];
}

int Mutante::soltarArma(Player *player){
    Mapa &mapa = player->getMapa();
    Item* arma = new Lanzacohetes(player->get_coordinates());
    mapa.agregarItem(arma, player->get_coordinates());
    this->tieneArma = false;
    return 4;
}

bool Mutante::estaListo(){
	return this->balas > configs[CONFIG::balas_gastadas_lanzacohetes]
	       && this->tieneArma;
}

int Mutante::numeroArma() const{
	return N_LANZACOHETES;
}

