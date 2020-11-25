#include "Mapa.h"
#include <iostream>
#include <utility>

// Codigo de errores en int (despues cambiar a excepciones)
// -1 lugar no encontrado
// -2 lugar ocupado

Mapa::Mapa(int alto, int ancho):alto(alto), ancho(ancho){
}

void Mapa::agregarJugador(Jugador* jugador){
    mapaJuego.insert(std::pair<Posicion, Posicionable*>
        (jugador->getPosicion(), jugador));
}

void Mapa::agregarPosicionable(Posicionable* posicionable, Posicion posicion){
    try{
        obtenerPosicionableEn(posicion);
        throw -2;
    } catch(int e){
        if (e == -1){
            mapaJuego.insert(std::pair<Posicion, Posicionable*>
                (posicion, posicionable));
        }
        if (e == -2)
            throw -2;
    }
}

void Mapa::sacarPosicionable(Posicion posicion){
    mapaJuego.erase(posicion);
}

Posicionable* Mapa::obtenerPosicionableEn(Posicion posicion){
    try{
        return mapaJuego.at(posicion);
    } catch(...) {
        throw -1;
    }
}

void Mapa::moveme(Jugador* jugador, Posicion& posicion){
    if (posicion.getPosX() > ancho || posicion.getPosY() > alto)
        throw -1;
    if (posicion.getPosX() < 0 || posicion.getPosY() < 0)
        throw -1;
    Posicion posJugador = jugador->getPosicion();
    if (jugador->getPosicion() == posicion){
        return;
    }
    try {
        agregarPosicionable(jugador, posicion);
        sacarPosicionable(posJugador);
    } catch(int e){
        throw;
    }
}

Mapa::~Mapa(){
}
