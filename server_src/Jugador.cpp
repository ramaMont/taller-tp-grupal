#include "Jugador.h"

#include <algorithm>
#include <iostream>


#define VIDA_MAXIMA 50 /*cambiar por yaml*/
#define CANTIDAD_DE_VIDAS 2
#define BALAS_INICIALES 8
#define BALAS_MAXIMAS 30
#define VIDA_MINIMA 11

Jugador::Jugador(Posicion posicion, Mapa& mapa): 
	Posicionable(posicion), posicion_inicial(posicion), mapa(mapa),
    setArmas(SetArmas(this->getPosicion())){
    mapa.agregarJugador(this);
    this->vida = VIDA_MAXIMA;
    this->vidasRestantes = CANTIDAD_DE_VIDAS;
    this->armaEquipada = this->setArmas.obtenerArma(N_PISTOLA);
    this->balas_restantes = BALAS_INICIALES;
	this->puntuacion = 0;
    this->balas_disparadas = 0;
    this->enemigos_matados = 0;
    this->llave = false;
}

void Jugador::mover(Direccion* direccion){
    Posicion nuevaPos = direccion->mover(this);
    try{
        mapa.moveme(this, nuevaPos);
        this->posicion = nuevaPos;
    } catch(...){
    }
}

void Jugador::recibirDanio(int danio){
	this->vida = std::max(this->vida - danio, 0);
	if (this->vida == 0)
		morir();
}

void Jugador::disparar(){
	this->armaEquipada->atacar(this);
}

bool Jugador::usar(Item* item){
	return item->usar(this);
}

bool Jugador::agregarArma(Arma* arma){
	return this->setArmas.agregarArma(arma);
}

bool Jugador::agregarVida(int cantidad){
	if (this->vida == VIDA_MAXIMA)
		return false;
	this->vida = std::min(this->vida + cantidad, VIDA_MAXIMA);
	return true;
}
	
void Jugador::agregarPuntos(int cantidad){
	this->puntuacion += cantidad;
}

bool Jugador::agregarBalas(int cant){
	if (this->balas_restantes == BALAS_MAXIMAS)
		return false;
	this->balas_restantes = std::min(this->balas_restantes+cant, BALAS_MAXIMAS);
	return true;
}

bool Jugador::agregarLlave(){
	if (this->llave)
		return false;
	this->llave = true;
	return true;
}

bool Jugador::estaPorMorir(){
	return this->vida <= VIDA_MINIMA;
}

void Jugador::morir(){
	this->setArmas.soltarArmas(this->mapa);
	Balas balas(this->posicion, 10);
	this->mapa.soltar(&balas);
	if (this->llave){
		Llave llave(this->posicion);
		this->mapa.soltar(&llave);
		this->llave = false;
	}
}

bool Jugador::revivir(){
	if (this->vidasRestantes <= 0)
		return false;
    mapa.agregarPosicionable(this, posicion_inicial);
    this->vida = VIDA_MAXIMA;
    this->vidasRestantes --;
    this->balas_restantes = BALAS_INICIALES;
	this->armaEquipada = this->setArmas.obtenerArma(N_PISTOLA);
    return true;
}


bool Jugador::estaVivo(){
	return ((this->vida > 0) || (this->vidasRestantes > 0));
}

Jugador::~Jugador(){
}


int Jugador::getVida(){
	return this->vida;
}

int Jugador::getBalas(){
	return this->balas_restantes;
}

size_t Jugador::getPuntuacion(){
	return this->puntuacion;
}

