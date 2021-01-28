#ifndef __CL_MAPA__
#define __CL_MAPA__

#include <vector>
#include <utility>
class Posicionable;
//#include "Posicionable.h"
class Character;
class Jugador;
//#include "Jugador.h"
class Enemy;
#include "coordinates.h"


class Cl_Mapa{
private:
    int alto;
    int ancho;
    std::vector<std::vector<Posicionable*>> mapaJuego;
    Character* player;
public:
    Cl_Mapa();
    explicit Cl_Mapa(int alto, int ancho);
    void agregarJugador(Character* jugador);
    void agregarPosicionable(Posicionable* posicionable, Coordinates posicion);
    void relocate(Character* jugador, Coordinates posicion);
    void sacarPosicionable(Coordinates posicion);
    Posicionable* obtenerPosicionableEn(Coordinates posicion);
    void moveme(Character* jugador, const Coordinates& posicion);
    void resize(int ancho, int alto);

    ~Cl_Mapa();
};

#endif
