#ifndef __MAPA__
#define __MAPA__

#include <vector>
#include <utility>
#include "Posicionable.h"
#include "Player.h"
class Player;
#include "Item.h"

#include "coordinates.h"

class Mapa{
private:
    int alto;
    int ancho;
    std::vector<std::vector<std::vector<Posicionable*>>> mapaJuego;
    std::vector<std::vector<std::vector<Item*>>> items;
public:
    explicit Mapa(int map_id);
    explicit Mapa(int alto, int ancho);
    void agregarPlayer(Player* jugador);
    void agregarPosicionable(Posicionable* posicionable, Coordinates posicion);
    void agregarItem(Item* item, Coordinates posicion);
    void sacarPosicionable(Coordinates posicion);
    void sacarItem(Coordinates posicion, const std::type_info& type_id);
    Posicionable* obtenerPosicionableEn(Coordinates posicion) const;
    void moveme(Player* jugador, const Coordinates& posicion);
//    Mapa(const Mapa&) = delete;
    Mapa(Mapa&& other);
//    Mapa& operator=(const Mapa&) = delete;
    Mapa& operator=(Mapa&& other);
    
    bool hayObstaculoEn(const Coordinates& posicion) const;
    bool hayObstaculoEn(float x, float y) const;
    bool hayPuertaEn(float x, float y) const;
    bool hayJugadorEn(float x, float y) const;
    int getAlto() const;
    int getAncho() const;    
    ~Mapa();
};

void initMap(Mapa& map);

#endif
