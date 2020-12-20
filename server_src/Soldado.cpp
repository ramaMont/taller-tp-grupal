#include "Soldado.h"

#include "Mapa.h"

#include <unistd.h>
#include <typeinfo>
#include <thread>
#include <chrono>

#include <iostream>

#define PRECISION 0.8
#define BALAS_AMETRALLADORA 5
#define TIEMPO_AMETRALLADORA 300
#define BALAS_LANZACOHETES 5
#define TIEMPO_CANION 100
#define GRADOS_180 180
#define GRADOS_45 45
#define PI 3.14159265358979323846


EstadoSoldado::EstadoSoldado(Jugador *jugador, int &balas): jugador(jugador),
    perro(Perro(balas)), guardia(Guardia(balas)), ss(SS(balas)),
    oficial(Oficial(balas)), mutante(Mutante(balas)){
	this->soldado = &guardia;
	this->soldado_anterior = nullptr;
}

int EstadoSoldado::armaActual() const{
	return this->soldado->numeroArma();
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
			return;
		case N_PISTOLA:
			if (this->guardia.estaListo())
				this->soldado = &this->guardia;
			return;
		case N_AMETRALLADORA:
			if (this->ss.estaListo())
				this->soldado = &this->ss;
			return;
		case N_CANION:
			if (this->oficial.estaListo())
				this->soldado = &this->oficial;
			return;
		case N_LANZACOHETES:
			if (this->mutante.estaListo())
				this->soldado = &this->mutante;
			return;
	}
}


void EstadoSoldado::soltarArma(){
	this->soldado->soltarArma(this->jugador);
}

void EstadoSoldado::disparar(std::vector<Jugador*>& enemigos){
	this->soldado->disparar(this->jugador, enemigos);
	if (!this->soldado->estaListo()){
		this->soldado_anterior = this->soldado;
		this->soldado = &this->perro;
	}
}

void EstadoSoldado::recargarBalas(){
	if (this->soldado_anterior){
		this->soldado = soldado_anterior;
		this->soldado_anterior = nullptr;
	}
}

// Perro

Perro::Perro(int& n): Soldado(n){
}

void Perro::disparar(Jugador *jugador, std::vector<Jugador*>& enemigos){
	std::set<std::pair<int, Jugador*>> set_jugadores;
	obtenerEnemigosCercanos(enemigos, jugador, set_jugadores);
	this->cuchillo.disparar(jugador, set_jugadores);
}

void Perro::soltarArma(Jugador *jugador){
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

void Soldado::obtenerEnemigosCercanos(std::vector<Jugador*>& enemigos,
    Jugador* jugador, std::set<std::pair<int, Jugador*>>& jugadores){
	for (Jugador* enemigo: enemigos){
		if (enemigo == jugador)  
			continue;
		float angulo = jugador->calcularAngulo(enemigo);
		int grados = radianesAGrados(angulo);
		if (grados <= GRADOS_45)
		    jugadores.insert(std::pair<int,Jugador*>(grados,enemigo));
	}
}


// Guardia

Guardia::Guardia(int& balas): Soldado(balas){
	this->pistola.setParametros(PRECISION);
}

void Guardia::disparar(Jugador *jugador, std::vector<Jugador*>& enemigos){
	std::set<std::pair<int, Jugador*>> set_jugadores;
	obtenerEnemigosCercanos(enemigos, jugador, set_jugadores);
	this->pistola.disparar(jugador, set_jugadores);
	this->balas --;
}

void Guardia::soltarArma(Jugador *jugador){
}

bool Guardia::estaListo(){
	return this->balas > 0;
}

int Guardia::numeroArma() const{
	return N_PISTOLA;
}


// SS

SS::SS(int &balas): Soldado(balas){
	this->ametralladora = nullptr;
}

bool SS::agregarArma(Ametralladora *ametr){
	if (this->ametralladora != nullptr)
		return false;
	this->ametralladora = ametr;
	this->ametralladora->setParametros(PRECISION);
	return true;
}

void SS::disparar(Jugador *jugador, std::vector<Jugador*>& enemigos){
	std::set<std::pair<int, Jugador*>> set_jugadores;
	obtenerEnemigosCercanos(enemigos, jugador, set_jugadores);
	float tiempo_presionado = 0.3;   /* Pasado por parametro */
	float tiempo_transcurrido = 0;
	while (tiempo_transcurrido < tiempo_presionado && this->balas > 0){
		for (int i = 0; (i < BALAS_AMETRALLADORA) && (this->balas > 0); i ++){
			this->ametralladora->disparar(jugador, set_jugadores);
			this->balas --;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(TIEMPO_AMETRALLADORA));
		tiempo_transcurrido += TIEMPO_AMETRALLADORA;
	}
}

void SS::soltarArma(Jugador *jugador){
	Mapa &mapa = jugador->getMapa();
	mapa.soltar(this->ametralladora, jugador->get_coordinates());
	this->ametralladora = nullptr;
}

bool SS::estaListo(){
	return this->balas > 0 && this->ametralladora != nullptr;
}

int SS::numeroArma() const{
	return N_AMETRALLADORA;
}


// Oficial

Oficial::Oficial(int &balas): Soldado(balas){
	this->canion = nullptr;
}

bool Oficial::agregarArma(CanionDeCadena *canion){
	if (this->canion != nullptr)
		return false;
	this->canion = canion;
	this->canion->setParametros(PRECISION);
    return true;
}
	
void Oficial::disparar(Jugador *jugador, std::vector<Jugador*>& enemigos){
	std::set<std::pair<int, Jugador*>> set_jugadores;
	obtenerEnemigosCercanos(enemigos, jugador, set_jugadores);
	for (int i = 0; (i < 1/*tiempo presionado*/) && (this->balas > 0); i ++){
		this->canion->disparar(jugador, set_jugadores);
		this->balas --;
		std::this_thread::sleep_for(std::chrono::milliseconds(TIEMPO_CANION));
	}	
}

void Oficial::soltarArma(Jugador *jugador){
	Mapa &mapa = jugador->getMapa();
	mapa.soltar(this->canion, jugador->get_coordinates());
	this->canion = nullptr;
}

bool Oficial::estaListo(){
	return this->balas > 0 && this->canion != nullptr;
}

int Oficial::numeroArma() const{
	return N_CANION;
}


// Mutante

Mutante::Mutante(int &balas): Soldado(balas){
	this->lanzacohetes = nullptr;
}

bool Mutante::agregarArma(Lanzacohetes *lanzacohetes){
	if (this->lanzacohetes != nullptr)
		return false;
	this->lanzacohetes = lanzacohetes;
	return true;	
}

void Mutante::disparar(Jugador *jugador, std::vector<Jugador*>& enemigos){
	this->lanzacohetes->disparar(jugador, enemigos);
	this->balas -= BALAS_LANZACOHETES;
}

void Mutante::soltarArma(Jugador *jugador){
	Mapa &mapa = jugador->getMapa();
	mapa.soltar(this->lanzacohetes, jugador->get_coordinates());
	this->lanzacohetes = nullptr;
}

bool Mutante::estaListo(){
	return this->balas > BALAS_LANZACOHETES && this->lanzacohetes != nullptr;
}

int Mutante::numeroArma() const{
	return N_LANZACOHETES;
}

