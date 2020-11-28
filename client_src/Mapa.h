#ifndef __MAPA__
#define __MAPA__

#include <unordered_map>
#include <utility>
#include "Posicionable.h"
#include "Jugador.h"
class Jugador;
#include "coordinates.h"

class Mapa{
private:
    int alto;
    int ancho;
    std::unordered_map<Coordinates, Posicionable*, Coordinates::Hash> mapaJuego;
public:
    explicit Mapa(int alto, int ancho);
    void agregarJugador(Jugador* jugador);
    void agregarPosicionable(Posicionable* posicionable, Coordinates posicion);
    void sacarPosicionable(Coordinates posicion);
    Posicionable* obtenerPosicionableEn(Coordinates posicion);
    void moveme(Jugador* jugador, Coordinates& posicion);
    ~Mapa();
};

#endif
