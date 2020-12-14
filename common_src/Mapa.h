#ifndef __MAPA__
#define __MAPA__

#include <vector>
#include <utility>
class Posicionable;
//#include "Posicionable.h"
class Movable;
class Jugador;
//#include "Jugador.h"
class Enemy;
#include "coordinates.h"


class Mapa{
private:
    int alto;
    int ancho;
    std::vector<std::vector<Posicionable*>> mapaJuego;
    Movable* player;
public:
    explicit Mapa(int alto, int ancho);
    void agregarJugador(Movable* jugador);
    void agregarPosicionable(Posicionable* posicionable, Coordinates posicion);
    void relocate(Movable* jugador, Coordinates posicion);
    void sacarPosicionable(Coordinates posicion);
    Posicionable* obtenerPosicionableEn(Coordinates posicion);
    void moveme(Movable* jugador, const Coordinates& posicion);
    ~Mapa();
};

#endif
