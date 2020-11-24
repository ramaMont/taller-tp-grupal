#include "Jugador.h"

Jugador::Jugador(Posicion posicion, Mapa& mapa):
        Posicionable(posicion), mapa(mapa){
    mapa.agregarJugador(this);
}

void Jugador::mover(Direccion* direccion){
    Posicion nuevaPos = direccion->mover(this);
    mapa.moveme(this, nuevaPos);
    this->posicion = nuevaPos;
}

Jugador::~Jugador(){
}
