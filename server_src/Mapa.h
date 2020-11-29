#ifndef __MAPA__
#define __MAPA__

#include <unordered_map>
#include <utility>
#include "Posicionable.h"
class Jugador;
#include "Jugador.h"
#include "Posicion.h"

class Mapa{
private:
    int alto;
    int ancho;
    std::unordered_map<Posicion, Posicionable*, Posicion::Hash> mapaJuego;
public:
    explicit Mapa(int alto, int ancho);
    void agregarJugador(Jugador* jugador);
    void agregarPosicionable(Posicionable* posicionable, Posicion posicion);
    void sacarPosicionable(Posicion posicion);
    Posicionable* obtenerPosicionableEn(Posicion posicion);
    void moveme(Jugador* jugador, Posicion& posicion);
    void soltar(Posicionable* objeto);
    ~Mapa();
};

#endif
