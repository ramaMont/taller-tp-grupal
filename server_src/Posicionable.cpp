#include "Posicionable.h"

Posicionable::Posicionable(Posicion posicion):
    posicion(posicion){
}

Posicion Posicionable::getPosicion(){
    return posicion;
}

Posicionable::~Posicionable(){
}
