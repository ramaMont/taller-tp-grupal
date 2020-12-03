#include "Objeto.h"

#include <thread>
#include <chrono>

#define SEGUNDOS_PUERTA 3

void ParedFalsa::abrir(Jugador *jugador){
	if (jugador->get_coordinates().calculate_distance(this->posicion) <= 1)
		jugador->getMapa().sacarPosicionable(this->posicion);
}


void Puerta::abrir(Jugador *jugador){
    abrirPuerta(jugador);
}

void Puerta::abrirPuerta(Jugador *jugador){
	if (jugador->get_coordinates().calculate_distance(this->posicion) > 1)
		return;
	this->puedo_pasar = true;
	
	// Cambiar a un evento
	std::this_thread::sleep_for (std::chrono::seconds(SEGUNDOS_PUERTA));
	cerrar();	
}

void Puerta::cerrar(){
	this->puedo_pasar = false;
}


void PuertaCerrada::abrir(Jugador *jugador){
	if (this->llave || jugador->usarLlave())
		abrirPuerta(jugador);
}
		
