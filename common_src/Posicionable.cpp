#include "Posicionable.h"

Posicionable::Posicionable(Coordinates posicion):
    posicion(posicion){
	this->puedo_pasar = false;
}

Coordinates Posicionable::getPosicion(){
    return posicion;
}

bool Posicionable::puedoPasar(){
	return this->puedo_pasar;
}

void Posicionable::puedoPasar(bool booleano){
	this->puedo_pasar = booleano;
}

Posicionable::~Posicionable(){
}
