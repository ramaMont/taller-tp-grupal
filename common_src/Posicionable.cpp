#include "Posicionable.h"

Posicionable::Posicionable(Coordinates posicion):
    posicion(posicion){
}

void Posicionable::set_texture(Texture *a_texture_drawer){
	texture_drawer = a_texture_drawer;
}

Coordinates Posicionable::get_position(){
    return posicion;
}

void Posicionable::colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
	throw -1;
}

Coordinates Posicionable::getPosicion(){
    return posicion;
}

Posicionable::~Posicionable(){
}
