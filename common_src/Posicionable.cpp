#include "Posicionable.h"

Posicionable::Posicionable(Coordinates posicion):
    posicion(posicion){
	this->esObstaculo = true;
}

Coordinates Posicionable::getPosicion(){
    return posicion;
}

bool Posicionable::atravesable(){
	return !this->esObstaculo;
}

void Posicionable::atravesable(bool booleano){
	this->esObstaculo = !booleano;
}

Posicionable::~Posicionable(){
}
