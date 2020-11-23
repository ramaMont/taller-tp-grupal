#include "Mapa.h"
#include <map>

Mapa::Mapa(){
}

void Mapa::agregarJugador(Jugador* jugador){
    mapaJuego.insert(std::pair<Posicion, Posicionable*>
        (jugador->getPosicion(), jugador));
}

void Mapa::agregarPosicionable(Posicionable* posicionable, Posicion posicion){
    mapaJuego.insert(std::pair<Posicion, Posicionable*>
        (posicion, posicionable));
}

void Mapa::sacarPosicionable(Posicion posicion){
    mapaJuego.erase(posicion);
}

Posicionable* Mapa::obtenerPosicionableEn(Posicion posicion){
    return mapaJuego.at(posicion);
}

Mapa::~Mapa(){
}
