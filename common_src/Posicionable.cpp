#include "Posicionable.h"

#include "texture.h"

Posicionable::Posicionable(Texture &texture_drawer,Coordinates posicion):
    posicion(posicion),texture_drawer(texture_drawer){
}

Coordinates Posicionable::get_position(){
    return posicion;
}

Intersected_object Posicionable::colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
	throw -1;
}

Posicionable::~Posicionable(){
}
