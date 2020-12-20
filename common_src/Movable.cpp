#include "Movable.h"
#include <stdio.h>

Movable::Movable(Texture &texture_drawer,Coordinates position,Coordinates direction ,Mapa& mapa):
        Posicionable(texture_drawer,position),direction(direction), mapa(mapa){
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

void Movable::set_direction(Coordinates direction){
    this->direction = direction;
}

Movable::~Movable(){
}
