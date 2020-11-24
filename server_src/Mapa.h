#ifndef __MAPA__
#define __MAPA__

#include <map>
#include <utility>
#include "Posicionable.h"
class Jugador;
#include "Jugador.h"


class Mapa{
private:
    std::map<Posicion, Posicionable*> mapaJuego;
public:
    Mapa();
    void agregarJugador(Jugador* jugador);
    void agregarPosicionable(Posicionable* posicionable, Posicion posicion);
    void sacarPosicionable(Posicion posicion);
    Posicionable* obtenerPosicionableEn(Posicion posicion);
    void moveme(Jugador* jugador, Posicion& posicion);
    ~Mapa();
};

#endif
