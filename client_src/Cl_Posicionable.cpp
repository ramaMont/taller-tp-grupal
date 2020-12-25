#include "Cl_Posicionable.h"

#include "texture.h"

Cl_Posicionable::Cl_Posicionable(Texture &texture_drawer,Coordinates posicion):
    posicion(posicion),texture_drawer(texture_drawer){
}

Coordinates Cl_Posicionable::get_position(){
    return posicion;
}

Intersected_object Cl_Posicionable::colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
	throw -1;
}

Cl_Posicionable::~Cl_Posicionable(){
}
