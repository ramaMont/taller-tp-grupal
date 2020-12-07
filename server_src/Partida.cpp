#include "Partida.h"
#include <string>
#include <iostream>
#include <set>

#define ALTO 20	/* cambiar por yaml */
#define ANCHO 20
#define MAXIMOS_JUGADORES 10
#define MINUTOS_PARTIDA 20

#define SEGUNDOS_POR_MINUTOS 60
#define CANT_GANADORES 5

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
	YAML::Node mapa_node = YAML::LoadFile("example_map.yaml");
	Mapa mapa(mapa_node["filas"].as<int>(), mapa_node["columnas"].as<int>());
	iniciarMapa(mapa, mapa_node["elementos"]);
	this->tiempo_inicial = time(0);
	recibirEventos();
}


void Partida::iniciarMapa(Mapa& mapa, YAML::Node elementos){
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
	std::string buffer;
	size_t (Jugador::*funcion)();
	
	buffer.append("Enemigos Matados:\n");
	funcion = &Jugador::getEnemigosMatados;
	mayoresPuntajes(buffer, funcion);
	
	buffer.append("Puntuacion:\n");
	funcion = &Jugador::getPuntuacion;
	mayoresPuntajes(buffer, funcion);
	
	funcion = &Jugador::getBalasDisparadas;
	buffer.append("Balas Disparadas:\n");
	mayoresPuntajes(buffer, funcion);

	std::cout << buffer;
}


void Partida::mayoresPuntajes(std::string& buffer,size_t (Jugador::*funcion)()){
	std::set<std::pair<size_t, std::string>> enemigos;
	
	for (std::pair<std::string, Jugador*> j: this->jugadores){
		std::pair<size_t, std::string> p((j.second->*funcion)(), j.first);
		enemigos.insert(p);
	}
	
	std::set<std::pair<size_t, std::string>>::reverse_iterator it;
	int i = 0;
	for (it = enemigos.rbegin(); it != enemigos.rend() && i<CANT_GANADORES; it++, i++)
		buffer.append((*it).first + "\t" + (*it).second + "\n");
	buffer.append("\n");	
}


Partida::~Partida(){
}
