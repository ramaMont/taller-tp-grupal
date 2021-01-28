#include "Character.h"
#include <stdio.h>

Character::Character(Coordinates position,Coordinates direction ,Cl_Mapa& mapa, int id):
        Posicionable(position),direction(direction), mapa(mapa), id(id){
}

void Character::mover_en_una_direccion(Direccion* direccion){
    Coordinates nuevaPos = direccion->mover(this,direction);

    Coordinates movimiento_unidireccional;
    movimiento_unidireccional.x = nuevaPos.x;
    movimiento_unidireccional.y = this->posicion.y;

    try{
        mapa.moveme(this, movimiento_unidireccional);
        this->posicion = movimiento_unidireccional;
    } catch(...){
    }

    movimiento_unidireccional.x = this->posicion.x;
    movimiento_unidireccional.y = nuevaPos.y;

    try{
        mapa.moveme(this, movimiento_unidireccional);
        this->posicion = movimiento_unidireccional;
    } catch(...){
    }

}

void Character::mover(Direccion* direccion){
    Coordinates nuevaPos = direccion->mover(this,direction);
    try{
        mapa.moveme(this, nuevaPos);
        this->posicion = nuevaPos;
    } catch(...){
        mover_en_una_direccion(direccion);
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
	mapa.sacarPosicionable(this->posicion);
}

void Character::resurrect(){
	//TODO: Resetear vida y demas atributos
    posicion = initial_position;
    direction = initial_direction;
	mapa.agregarPosicionable(this, this->initial_position);
}

Character::~Character(){
}
