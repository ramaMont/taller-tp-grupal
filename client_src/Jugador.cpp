#include "Jugador.h"

static float inc = 0.05;

Jugador::Jugador(Coordinates position,Coordinates direction ,Mapa& mapa):
        Posicionable(position),direction(direction), mapa(mapa){
    mapa.agregarJugador(this);
}

void Jugador::mover(Direccion* direccion){

    Coordinates nuevaPos = direccion->mover(this,direction);
    try{
        mapa.moveme(this, nuevaPos);
        this->posicion = nuevaPos;
    } catch(...){
    }
}

void Jugador::rotate_left(){
	direction.rotate(inc);
}

void Jugador::rotate_right(){
	direction.rotate(-inc);	
}

Jugador::~Jugador(){
}

Coordinates Jugador::get_coordinates(){
    return posicion;
}

Coordinates Jugador::get_direction(){
    return direction;
}
