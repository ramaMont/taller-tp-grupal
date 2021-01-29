#include "Character.h"
#include <stdio.h>

Character::Character(Coordinates position,Coordinates direction ,ClMap& map, int id):
        Posicionable(position),direction(direction), map(map), id(id){
}

void Character::move_in_one_direction(Direccion* direccion){
    Coordinates nuevaPos = direccion->mover(this,direction);

    Coordinates movimiento_unidireccional;
    movimiento_unidireccional.x = nuevaPos.x;
    movimiento_unidireccional.y = this->posicion.y;

    try{
        map.moveme(this, movimiento_unidireccional);
        this->posicion = movimiento_unidireccional;
    } catch(...){
    }

    movimiento_unidireccional.x = this->posicion.x;
    movimiento_unidireccional.y = nuevaPos.y;

    try{
        map.moveme(this, movimiento_unidireccional);
        this->posicion = movimiento_unidireccional;
    } catch(...){
    }

}

void Character::mover(Direccion* direccion){
    Coordinates nuevaPos = direccion->mover(this,direction);
    try{
        map.moveme(this, nuevaPos);
        this->posicion = nuevaPos;
    } catch(...){
        move_in_one_direction(direccion);
    }
}

Coordinates Character::get_direction() const{
    return direction;
}

int Character::getId(){
    return id;
}

void Character::set_direction(Coordinates direction){
    this->direction = direction;
}

void Character::setInitialPosition(Coordinates initial_position){
    this->initial_position = initial_position;
}

void Character::die(){
	//TODO: Animaciones de muerte =O.
	map.removePositionable(this->posicion);
}

void Character::resurrect(){
	//TODO: Resetear vida y demas atributos
    posicion = initial_position;
    direction = initial_direction;
	map.addPositionable(this, this->initial_position);
}

Character::~Character(){
}
