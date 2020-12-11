#ifndef __MAPA__
#define __MAPA__

#include <vector>
#include <utility>
class Posicionable;
//#include "Posicionable.h"
class Jugador;
//#include "Jugador.h"
#include "coordinates.h"


class Mapa{
private:
    int alto;
    int ancho;
    std::vector<std::vector<Posicionable*>> mapaJuego;
    Jugador* player;
public:
    explicit Mapa(int alto, int ancho);
    void agregarJugador(Jugador* jugador);
    void agregarPosicionable(Posicionable* posicionable, Coordinates posicion);
    void sacarPosicionable(Coordinates posicion);
    Posicionable* obtenerPosicionableEn(Coordinates posicion);
    void moveme(Jugador* jugador, const Coordinates& posicion);
    ~Mapa();
};

#endif
