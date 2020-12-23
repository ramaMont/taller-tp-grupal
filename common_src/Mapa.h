#ifndef __MAPA__
#define __MAPA__

#include <vector>
#include <utility>
#include "Posicionable.h"
#include "Player.h"
class Player;
#include "coordinates.h"

class Mapa{
private:
    int alto;
    int ancho;
    std::vector<std::vector<Posicionable*>> mapaJuego;
public:
    explicit Mapa(int map_id);
    explicit Mapa(int alto, int ancho);
    void agregarPlayer(Player* jugador);
    void agregarPosicionable(Posicionable* posicionable, Coordinates posicion);
    void sacarPosicionable(Coordinates posicion);
    Posicionable* obtenerPosicionableEn(Coordinates posicion);
    void moveme(Player* jugador, const Coordinates& posicion);
//    Mapa(const Mapa&) = delete;
    Mapa(Mapa&& other);
//    Mapa& operator=(const Mapa&) = delete;
    Mapa& operator=(Mapa&& other);
    ~Mapa();
};

void initMap(Mapa& map);

#endif
