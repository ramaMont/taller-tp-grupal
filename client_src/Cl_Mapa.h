#ifndef __CL_MAPA__
#define __CL_MAPA__

#include <vector>
#include <utility>
class Posicionable;
//#include "Posicionable.h"
class Movable;
class Jugador;
//#include "Jugador.h"
class Enemy;
#include "coordinates.h"


class Cl_Mapa{
private:
    int alto;
    int ancho;
    std::vector<std::vector<Posicionable*>> mapaJuego;
    Movable* player;
public:
    explicit Cl_Mapa(int alto, int ancho);
    void agregarJugador(Movable* jugador);
    void agregarPosicionable(Posicionable* posicionable, Coordinates posicion);
    void relocate(Movable* jugador, Coordinates posicion);
    void sacarPosicionable(Coordinates posicion);
    Posicionable* obtenerPosicionableEn(Coordinates posicion);
    void moveme(Movable* jugador, const Coordinates& posicion);

    void delete_element(Coordinates position_to_remove);

    ~Cl_Mapa();
};

#endif
