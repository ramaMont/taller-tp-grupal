#include "Objeto.h"

#include <ConfigVariable.h>
class Mapa;
#include "Mapa.h"

Coordinates& Objeto::getCoordinates(){
    return this->posicion;
}


ParedFalsa::ParedFalsa(Coordinates coordenadas): Objeto(coordenadas) {
    posicion.x += 0.5;  // Para estar en el centro de la posicion
    posicion.y += 0.5;  // Para estar en el centro de la posicion
}
bool ParedFalsa::abrir(Player *jugador){
    double angle = jugador->get_coordinates().calculate_angle(
        jugador->get_direction(), posicion);
    return (angle < 1);
}


Puerta::Puerta(Coordinates coordenadas): Objeto(coordenadas) {
    posicion.x += 0.5;  // Para estar en el centro de la posicion
    posicion.y += 0.5;  // Para estar en el centro de la posicion
}

bool Puerta::abrir(Player *jugador){
    return abrirPuerta(jugador);
}

bool Puerta::abrirPuerta(Player *jugador){
    double angle = jugador->get_coordinates().calculate_angle(
        jugador->get_direction(), posicion);
    if (angle < 1){
        atravesable(true);
        return true;
    }
    return false;
}

void Puerta::cerrar(){
	atravesable(false);
}


bool PuertaCerrada::abrir(Player *jugador){
	if (this->llave || jugador->usarLlave())
		return abrirPuerta(jugador);
    return false;
}
		
