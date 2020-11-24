#include "Mapa.h"
#include <iostream>
#include <utility>

Mapa::Mapa(int alto, int ancho):alto(alto), ancho(ancho){
}

void Mapa::agregarJugador(Jugador* jugador){
    mapaJuego.insert(std::pair<Posicion, Posicionable*>
        (jugador->getPosicion(), jugador));
}

void Mapa::agregarPosicionable(Posicionable* posicionable, Posicion posicion){
    Posicionable* retorno = obtenerPosicionableEn(posicion);
    if (retorno != NULL){
        retorno = NULL;
        throw -1;
    }
    std::cout << "voy a insertar\n";
    mapaJuego.insert(std::pair<Posicion, Posicionable*>
        (posicion, posicionable));
}

void Mapa::sacarPosicionable(Posicion posicion){
    mapaJuego.erase(posicion);
}

Posicionable* Mapa::obtenerPosicionableEn(Posicion posicion){
    try{
        return mapaJuego.at(posicion);
    } catch(...) {
        return NULL;
    }
}

void Mapa::moveme(Jugador* jugador, Posicion& posicion){
    if (posicion.getPosX() > ancho || posicion.getPosY() > alto)
        throw -1;
    if (posicion.getPosX() < 0 || posicion.getPosY() < 0)
        throw -1;
    Posicion posJugador = jugador->getPosicion();
    agregarPosicionable(jugador, posicion);
//    sacarPosicionable(posJugador);
}

Mapa::~Mapa(){
}
