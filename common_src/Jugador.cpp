#include "Jugador.h"
#include <stdio.h>

Jugador::Jugador(Coordinates position,Coordinates direction ,Mapa& mapa):
        Posicionable(position),direction(direction), mapa(mapa){
    mapa.agregarJugador(this);
}

void Jugador::mover_en_una_direccion(Direccion* direccion){
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

void Jugador::mover(Direccion* direccion){
    Coordinates nuevaPos = direccion->mover(this,direction);
    try{
        mapa.moveme(this, nuevaPos);
        this->posicion = nuevaPos;
    } catch(...){
        mover_en_una_direccion(direccion);
    }
}

Coordinates Jugador::get_coordinates(){
    return posicion;
}

Coordinates Jugador::get_direction(){
    return direction;
}

void Jugador::set_direction(Coordinates direction){
    this->direction = direction;
}

Jugador::~Jugador(){
}
