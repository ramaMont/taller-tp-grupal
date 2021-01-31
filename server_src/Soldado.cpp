#include "Soldado.h"

#include "Mapa.h"
#include <ConfigVariable.h>

#include <unistd.h>
#include <typeinfo>
#include <thread>
#include <chrono>
#include <iostream>
#define GRADOS_180 180
#define PI 3.14159265358979323846


EstadoSoldado::EstadoSoldado(Player *jugador, int &balas): jugador(jugador),
    perro(Perro(balas)), guardia(Guardia(balas)), ss(SS(balas)),
    oficial(Oficial(balas)), mutante(Mutante(balas)), arma_actual(1){
	this->soldado = &guardia;
	this->soldado_anterior = nullptr;
}

int EstadoSoldado::armaActual() const{
	return this->arma_actual;
}

bool EstadoSoldado::agregarArma(Arma* arma){
	if (typeid(*arma) == typeid(Ametralladora)){
		return this->ss.agregarArma(static_cast<Ametralladora*>(arma));
	}
	if (typeid(*arma) == typeid(CanionDeCadena)){
		return this->oficial.agregarArma(static_cast<CanionDeCadena*>(arma));
	}
	if (typeid(*arma) == typeid(Lanzacohetes)){
		return this->mutante.agregarArma(static_cast<Lanzacohetes*>(arma));
	}
	return false;
}

void EstadoSoldado::cambiarArma(int numero_arma){
	switch (numero_arma){
		case N_CUCHILLO:
			this->soldado = &this->perro;
			break;
		case N_PISTOLA:
			if (this->guardia.estaListo())
				this->soldado = &this->guardia;
			break;
		case N_AMETRALLADORA:
			if (this->ss.estaListo())
				this->soldado = &this->ss;
			break;
		case N_CANION:
			if (this->oficial.estaListo())
				this->soldado = &this->oficial;
			break;
		case N_LANZACOHETES:
			if (this->mutante.estaListo())
				this->soldado = &this->mutante;
			break;
	}
	this->arma_actual = this->soldado->numeroArma();
}


int EstadoSoldado::soltarArma(){
	return this->soldado->soltarArma(this->jugador);
}

int EstadoSoldado::disparar(std::map<int, Player*>& enemigos){
	int balas_disparadas = this->soldado->disparar(this->jugador, enemigos);
	if (!this->soldado->estaListo()){
		this->soldado_anterior = this->soldado;
		this->soldado = &this->perro;
	}
	this->arma_actual = this->soldado->numeroArma();
	return balas_disparadas;
}

void EstadoSoldado::recargarBalas(){
	if (this->soldado_anterior){
		this->soldado = soldado_anterior;
		this->soldado_anterior = nullptr;
	}
	this->arma_actual = this->soldado->numeroArma();
}

// Perro

Perro::Perro(int& n): Soldado(n){
}

int Perro::disparar(Player *jugador, std::map<int, Player*>& enemigos){
	std::set<std::pair<int, Player*>> set_jugadores;
	obtenerEnemigosCercanos(enemigos, jugador, set_jugadores);
	this->cuchillo.disparar(jugador, set_jugadores);
	return 0;
}

int Perro::soltarArma(Player *jugador){
	return 0;
}

bool Perro::estaListo(){
	return true;
}

int Perro::numeroArma() const{
	return N_CUCHILLO;
}


// Soldado

int radianesAGrados(double radianes){
	return radianes * GRADOS_180 / PI;
}

void Soldado::obtenerEnemigosCercanos(std::map<int, Player*>& enemigos,
    Player* jugador, std::set<std::pair<int, Player*>>& jugadores){
    for (auto it = enemigos.begin(); it != enemigos.end(); ++it){
        auto enemigo = it->second;
		if (enemigo == jugador)  
			continue;
		float angulo = jugador->calcularAngulo(enemigo);
		int grados = radianesAGrados(angulo);
		if (grados <= configs[CONFIG::rango_de_disparo])
		    jugadores.insert(std::pair<int,Player*>(grados,enemigo));
	}
}


// Guardia

Guardia::Guardia(int& balas): Soldado(balas){
}

int Guardia::disparar(Player *jugador, std::map<int, Player*>& enemigos){
	std::set<std::pair<int, Player*>> set_jugadores;
	obtenerEnemigosCercanos(enemigos, jugador, set_jugadores);
	this->pistola.disparar(jugador, set_jugadores);
	this->balas --;
	return 1;
}

int Guardia::soltarArma(Player *jugador){
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

int SS::disparar(Player *jugador, std::map<int, Player*>& enemigos){
	std::set<std::pair<int, Player*>> set_jugadores;
	obtenerEnemigosCercanos(enemigos, jugador, set_jugadores);
	
	int balas_disparadas = 0;
	for (int i = 0; (i < configs[CONFIG::balas_rafaga_ametralladora]) 
	    && (this->balas > 0); i++){
	    this->ametralladora.disparar(jugador, set_jugadores);
	    this->balas --;
	    balas_disparadas ++;
	}
	return balas_disparadas;
}

int SS::soltarArma(Player *jugador){
    Mapa &mapa = jugador->getMapa();
    Item* arma = new Ametralladora(jugador->get_coordinates());
    mapa.agregarItem(arma, jugador->get_coordinates());
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
	
int Oficial::disparar(Player *jugador, std::map<int, Player*>& enemigos){
	std::set<std::pair<int, Player*>> set_jugadores;
	obtenerEnemigosCercanos(enemigos, jugador, set_jugadores);
	this->canion.disparar(jugador, set_jugadores);
	this->balas --;	
	return 1;
}

int Oficial::soltarArma(Player *jugador){
    Mapa &mapa = jugador->getMapa();
    Item* arma = new CanionDeCadena(jugador->get_coordinates());
    mapa.agregarItem(arma, jugador->get_coordinates());
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

int Mutante::disparar(Player *jugador, std::map<int, Player*>& enemigos){
	this->lanzacohetes.disparar(jugador, enemigos);
	this->balas -= (int)configs[CONFIG::balas_gastadas_lanzacohetes];
	return (int)configs[CONFIG::balas_gastadas_lanzacohetes];
}

int Mutante::soltarArma(Player *jugador){
    Mapa &mapa = jugador->getMapa();
    Item* arma = new Lanzacohetes(jugador->get_coordinates());
    mapa.agregarItem(arma, jugador->get_coordinates());
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

