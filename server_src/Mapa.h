#ifndef __MAPA__
#define __MAPA__

#include <vector>
#include <stack>
#include <utility>
#include "Posicionable.h"
#include "Jugador.h"
class Jugador;
#include "coordinates.h"


class Mapa{
private:
    int alto;
    int ancho;
    std::vector<std::vector<std::stack<Posicionable*>>> mapaJuego;
public:
    explicit Mapa(int alto, int ancho);
    void agregarJugador(Jugador* jugador);
    void agregarPosicionable(Posicionable* posicionable, Coordinates posicion);
    void sacarPosicionable(Coordinates posicion);
    Posicionable* obtenerPosicionableEn(Coordinates posicion) const;
    void moveme(Jugador* jugador, const Coordinates& posicion);
    void soltar(Posicionable* objeto, const Coordinates& posicion);
    void soltar(Posicionable objeto);
    bool hayObstaculoEn(const Coordinates& posicion) const;
    bool hayObstaculoEn(float x, float y) const;
    bool hayPuertaEn(float x, float y) const;
    int getAlto() const;
    int getAncho() const;
    ~Mapa();
};

#endif
