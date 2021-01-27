#include "Movable.h"
#include <stdio.h>

Movable::Movable(Coordinates position,Coordinates direction ,Cl_Mapa& mapa, int id):
        Posicionable(position),direction(direction), mapa(mapa), id(id){
}

void Movable::mover_en_una_direccion(Direccion* direccion){
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

void Movable::mover(Direccion* direccion){
    Coordinates nuevaPos = direccion->mover(this,direction);
    try{
        mapa.moveme(this, nuevaPos);
        this->posicion = nuevaPos;
    } catch(...){
        mover_en_una_direccion(direccion);
    }
}

Coordinates Movable::get_direction() const{
    return direction;
}

int Movable::getId(){
    return id;
}

void Movable::set_direction(Coordinates direction){
    this->direction = direction;
}

void Movable::setInitialPosition(Coordinates initial_position){
    this->initial_position = initial_position;
}

void Movable::die(){
	//TODO: Animaciones de muerte =O.
	mapa.sacarPosicionable(this->posicion);
}

void Movable::resurrect(){
	//TODO: Resetear vida y demas atributos
    posicion = initial_position;
    direction = initial_direction;
	mapa.agregarPosicionable(this, this->initial_position);
}

Movable::~Movable(){
}
