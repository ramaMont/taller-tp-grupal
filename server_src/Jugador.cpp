#include "Jugador.h"
#include "ParamReaderServer.h"
#include <stdio.h>
#include <algorithm>
#include <iostream>


Jugador::Jugador(Coordinates position, Coordinates direction, Mapa& mapa):
    Posicionable(position), mapa(mapa), direction(direction),
    soldado(EstadoSoldado(this, this->balas_restantes)){
    mapa.agregarJugador(this);
    this->vida = (int)configuracion["vida_maxima"];
    this->vidasRestantes = (int)configuracion["cantidad_de_vidas"];
    this->balas_restantes = (int)configuracion["balas_iniciales"];
	this->puntuacion = 0;
    this->balas_disparadas = 0;
    this->enemigos_matados = 0;
    this->llave = false;    
}

void Jugador::mover(Direccion* direccion){
    Coordinates nuevaPos = direccion->mover(this,direction);
    try{
        mapa.moveme(this, nuevaPos);//Esto explota
        this->posicion = nuevaPos;
    } catch(...){
    }
}

Coordinates Jugador::get_coordinates() const{
    return posicion;
}

Coordinates Jugador::get_direction() const{
    return direction;
}

void Jugador::set_direction(Coordinates direction){
    this->direction = direction;
}


double Jugador::calcularAngulo(Jugador* jugador){
	return jugador->calcularAngulo(this->direction, this->posicion);
}

double Jugador::calcularAngulo(const Coordinates& direccion, const Coordinates& posicion){
	return posicion.calculate_angle(direccion, this->posicion);
}

double Jugador::calcularDistancia(Jugador* jugador){
	return jugador->calcularDistancia(this->posicion);
}

double Jugador::calcularDistancia(const Coordinates& posicion){
	return posicion.calculate_distance(this->posicion);
}


bool Jugador::recibirDanio(int danio){
	this->vida = std::max(this->vida - danio, 0);
	if (this->vida == 0){
		morir();
		return true;
	}
	return false;
}

void Jugador::disparar(std::vector<Jugador*>& jugadores){
	this->soldado.disparar(jugadores);
}

bool Jugador::usar(Item* item){
	return item->usar(this);
}

bool Jugador::agregarArma(Arma* arma){
	return this->soldado.agregarArma(arma);
}

void Jugador::cambiarArma(int numero_arma){
	this->soldado.cambiarArma(numero_arma);
}

bool Jugador::agregarVida(int cantidad){
	if (this->vida == (int)configuracion["vida_maxima"])
		return false;
	this->vida = std::min(this->vida + cantidad, (int)configuracion["vida_maxima"]);
	return true;
}
	
void Jugador::agregarPuntos(int cantidad){
	this->puntuacion += cantidad;
}

bool Jugador::agregarBalas(int cant){
	if (this->balas_restantes == (int)configuracion["balas_maximas"])
		return false;
	this->balas_restantes = std::min(this->balas_restantes+cant, 
	    (int)configuracion["balas_maximas"]);
	this->soldado.recargarBalas();
	return true;
}

bool Jugador::agregarLlave(){
	if (this->llave)
		return false;
	this->llave = true;
	return true;
}

bool Jugador::usarLlave(){
	bool aux = this->llave;
	this->llave = false;
	return aux;
}

void Jugador::agregarEnemigoMuerto(){
	this->enemigos_matados ++;
}

bool Jugador::estaPorMorir(){
	return this->vida <= (int)configuracion["vida_minima"];
}

void Jugador::morir(){
	this->soldado.soltarArma();
	this->mapa.soltar(Balas(this->posicion, 10));
	if (this->llave){
		this->mapa.soltar(Llave(this->posicion));
		this->llave = false;
	}
	revivir();
}

bool Jugador::revivir(){
	if (this->vidasRestantes <= 0)
		return false;
    mapa.agregarPosicionable(this, posicion_inicial);
    this->vida = (int)configuracion["vida_maxima"];
    this->vidasRestantes --;
    this->balas_restantes = (int)configuracion["balas_iniciales"];
	this->soldado.cambiarArma(N_PISTOLA);
    return true;
}

bool Jugador::estaVivo(){
	return ((this->vida > 0) || (this->vidasRestantes > 0));
}

Mapa& Jugador::getMapa(){
	return this->mapa;
}

int Jugador::numeroArmaActual() const{
	return this->soldado.armaActual();
}

size_t Jugador::getBalasDisparadas(){
	return this->balas_disparadas;
}

size_t Jugador::getEnemigosMatados(){
	return this->enemigos_matados;
}

size_t Jugador::getPuntuacion(){
	return this->puntuacion;
}

int Jugador::getVida(){
	return this->vida;
}

int Jugador::getBalas(){
	return this->balas_restantes;
}


Jugador::~Jugador(){
}

