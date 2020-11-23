#ifndef __MAPA__
#define __MAPA__

class Jugador;
#include "Jugador.h"
#include "Posicionable.h"
#include <map>
#include <utility>


class Mapa{
private:
    std::map<Posicion, Posicionable*> mapaJuego;
public:
    Mapa();
    void agregarJugador(Jugador* jugador);
    void agregarPosicionable(Posicionable* posicionable, Posicion posicion);
    void sacarPosicionable(Posicion posicion);
    Posicionable* obtenerPosicionableEn(Posicion posicion);
    ~Mapa();
};

#endif
