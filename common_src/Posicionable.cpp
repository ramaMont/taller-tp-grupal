#include "Posicionable.h"


Posicionable::Posicionable(Coordinates posicion):
    posicion(posicion){
}

Posicionable::Posicionable(Coordinates posicion, int texture):
    posicion(posicion),texture(texture){
}

Coordinates Posicionable::getPosicion(){
    return posicion;
}

Intersected_object Posicionable::colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
	throw -1;
}

Posicionable::~Posicionable(){
}
