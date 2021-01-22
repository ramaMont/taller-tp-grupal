#include "Objeto.h"

#include <ConfigVariable.h>
class Mapa;
#include "Mapa.h"
#include <thread>
#include <chrono>

Coordinates& Objeto::getCoordinates(){
    return this->posicion;
}

bool ParedFalsa::abrir(Player *jugador){
	return true;
}


bool Puerta::abrir(Player *jugador){
    return abrirPuerta(jugador);
}

bool Puerta::abrirPuerta(Player *jugador){
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
		
