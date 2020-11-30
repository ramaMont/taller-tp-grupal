#include "Partida.h"
#include <string>
#include <iostream>

#define ALTO 20	/* cambiar por yaml */
#define ANCHO 20
#define MAXIMOS_JUGADORES 10
#define MINUTOS_PARTIDA 20

#define SEGUNDOS_POR_MINUTOS 60

Partida::Partida(const std::string& params): params(params){
}


void Partida::run(){
}


bool Partida::agregarJugador(const std::string& nombre){
	if (this->jugadores.size() == MAXIMOS_JUGADORES)
		return false;
	this->jugadores[nombre] = nullptr;
	return true;
}


void Partida::agregarRobot(){
	this->robots.push_back(nullptr);
}


void Partida::comenzarPartida(){
	if (this->jugadores.size() == 0)
		return;
	Mapa mapa(ALTO,ANCHO);
	iniciarMapa(mapa);
	this->tiempo_inicial = time(0);
	recibirEventos();
}


void Partida::iniciarMapa(Mapa& mapa){
	// Colocar objetos, jugadores y robots en el mapa
}


void Partida::recibirEventos(){
	while (true){
		// realizar evento
		time_t tiempo_actual = time(0);
		double segundos = difftime(tiempo_actual, this->tiempo_inicial);
		if (segundos/SEGUNDOS_POR_MINUTOS > MINUTOS_PARTIDA)
			break;
		if (todosMuertos())
			break;
	}
	mostrarGanadores();
}


bool Partida::todosMuertos(){
	bool ganador = false;
	for (std::pair<std::string,Jugador*> j: this->jugadores){
		if (j.second->estaVivo()){
			if (ganador)
				return false;
			ganador = true;
		}
	}
	for (Jugador* j: this->robots){
		if (j->estaVivo()){
			if (ganador)
				return false;
			ganador = true;
		}
	}
	return true;
}


void Partida::mostrarGanadores(){
}


Partida::~Partida(){
}
