#include "Jugador.h"

Jugador::Jugador(Posicion posicion, Mapa& mapa):
        Posicionable(posicion), mapa(mapa){
    mapa.agregarJugador(this);
}

void Jugador::mover(Direccion* direccion){
//    this->movimiento->mover(direccion, this);
    Posicion nuevaPos = direccion->mover(this);
    mapa.moveme(this, nuevaPos);
    this->posicion = nuevaPos;
}

Jugador::~Jugador(){

}