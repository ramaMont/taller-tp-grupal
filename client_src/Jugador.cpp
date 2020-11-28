#include "Jugador.h"
#include <stdio.h>

Jugador::Jugador(Coordinates position,Coordinates direction ,Mapa& mapa):
        Posicionable(position),direction(direction), mapa(mapa){
    mapa.agregarJugador(this);
}

void Jugador::mover(Direccion* direccion){
    Coordinates nuevaPos = direccion->mover(this,direction);
    try{
        mapa.moveme(this, nuevaPos);//Esto explota
        this->posicion = nuevaPos;
    } catch(...){
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
