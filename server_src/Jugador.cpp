#include "Jugador.h"

Jugador::Jugador(Posicion posicion, Mapa& mapa):
        Posicionable(posicion), mapa(mapa){
    mapa.agregarJugador(this);
}

void Jugador::mover(Direccion* direccion){
    Posicion nuevaPos = direccion->mover(this);
    try{
        mapa.moveme(this, nuevaPos);
        this->posicion = nuevaPos;
    } catch(...){
    }
}

void Jugador::setPosicion(Posicion posicion){
    this->posicion = posicion;
}

Jugador::~Jugador(){
}
