#include "Posicionable.h"

Posicionable::Posicionable():
	texture_drawer(nullptr),  esObstaculo(true){
}

Posicionable::Posicionable(Coordinates posicion):
    posicion(posicion){
	this->esObstaculo = true;
}

Posicionable::Posicionable(Coordinates posicion, Coordinates direction):
    posicion(posicion), direction(direction){
	this->esObstaculo = true;
}

void Posicionable::set_texture(Texture *a_texture_drawer){
	texture_drawer = a_texture_drawer;
}

Coordinates Posicionable::get_position(){
    return posicion;
}

Coordinates Posicionable::get_direction(){
	return direction;
}
void Posicionable::setDirection(Coordinates direction){
	this->direction = direction;
}

void Posicionable::colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
	throw -1;
}

Coordinates Posicionable::get_coordinates(){
	return posicion;
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
