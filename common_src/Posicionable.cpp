#include "Posicionable.h"

Posicionable::Posicionable(Coordinates posicion):
    posicion(posicion){
}

Coordinates Posicionable::getPosicion(){
    return posicion;
}

Posicionable::~Posicionable(){
}
