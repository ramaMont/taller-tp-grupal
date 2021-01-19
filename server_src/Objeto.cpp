#include "Objeto.h"

#include <ConfigVariable.h>
#include "Mapa.h"
#include <thread>
#include <chrono>


void ParedFalsa::abrir(Player *jugador){
	if (jugador->get_coordinates().calculate_distance(this->posicion) <= 1)
		jugador->getMapa().sacarPosicionable(this->posicion);
}


void Puerta::abrir(Player *jugador){
    abrirPuerta(jugador);
}

void Puerta::abrirPuerta(Player *jugador){
	if (jugador->get_coordinates().calculate_distance(this->posicion) > 1)
		return;
	atravesable(true);
	
	// Cambiar a un evento
	std::this_thread::sleep_for (std::chrono::seconds(
	    (int)configs[CONFIG::segundos_cerrar_puerta]));
	cerrar();	
}

void Puerta::cerrar(){
	atravesable(false);
}


void PuertaCerrada::abrir(Player *jugador){
	if (this->llave || jugador->usarLlave())
		abrirPuerta(jugador);
}
		
