#include "Objeto.h"

#include <ConfigVariable.h>
#include "Mapa.h"
#include <thread>
#include <chrono>


bool ParedFalsa::abrir(Player *jugador){
	if (jugador->get_coordinates().calculate_distance(this->posicion) <= 1)
		return true;
    return false;
}


bool Puerta::abrir(Player *jugador){
    return abrirPuerta(jugador);
}

bool Puerta::abrirPuerta(Player *jugador){
	if (jugador->get_coordinates().calculate_distance(this->posicion) > 1)
		return false;
	atravesable(true);
    return true;
}

void Puerta::cerrar(){
	atravesable(false);
}


bool PuertaCerrada::abrir(Player *jugador){
	if (this->llave || jugador->usarLlave())
		return abrirPuerta(jugador);
    return false;
}
		
