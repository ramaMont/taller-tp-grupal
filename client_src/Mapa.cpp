#include "Mapa.h"
#include <iostream>
#include <utility>

// Codigo de errores en int (despues cambiar a excepciones)
// -1 lugar no encontrado
// -2 lugar ocupado

Mapa::Mapa(int alto, int ancho):alto(alto), ancho(ancho){
}

void Mapa::agregarJugador(Jugador* jugador){
    mapaJuego.insert(std::pair<Coordinates, Posicionable*>
        (jugador->getPosicion(), jugador));
}

void Mapa::agregarPosicionable(Posicionable* posicionable, Coordinates posicion){
    try{
        obtenerPosicionableEn(posicion);
        throw -2;
    } catch(int e){
        if (e == -1){
            mapaJuego.insert(std::pair<Coordinates, Posicionable*>
                (posicion, posicionable));
        }
        if (e == -2)
            throw -2;
    }
}

void Mapa::sacarPosicionable(Coordinates posicion){
    mapaJuego.erase(posicion);
}

Posicionable* Mapa::obtenerPosicionableEn(Coordinates posicion){
    return mapaJuego.at(posicion);

}

void Mapa::moveme(Jugador* jugador, Coordinates& posicion){
    if (posicion.x > ancho || posicion.y > alto)
        throw -1;
    if (posicion.x < 0 || posicion.y < 0)
        throw -1;
    Coordinates posJugador = jugador->getPosicion();
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
