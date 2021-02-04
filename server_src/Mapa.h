#ifndef __MAPA__
#define __MAPA__

#include <vector>
#include <utility>
#include "Posicionable.h"
#include "Player.h"
class Player;
#include "Item.h"
class Objeto;
class Puerta;
#include "Objeto.h"

#include "coordinates.h"
#include <yaml-cpp/yaml.h>
#include <map>
#include <tuple>

class Mapa{
private:
    int alto;
    int ancho;
    std::vector<std::vector<std::vector<Posicionable*>>> mapaJuego;
    std::vector<std::vector<std::vector<Item*>>> items;
    std::vector<Objeto*> passages;
    std::vector<std::tuple<Coordinates, std::string>> player_positions;
    int players_added;
    void initMap(Mapa& map, YAML::Node map_node);


public:
    explicit Mapa(std::string map_filename);
    explicit Mapa(int alto, int ancho);
    void agregarPlayer(Player* jugador);
    void respawnPlayer(Player* jugador);
    void agregarPosicionable(Posicionable* posicionable, Coordinates posicion);
    void agregarItem(Item* item, Coordinates posicion);
    Coordinates throwItem(Item* item, Coordinates posicion);
    void addPassage(Objeto* passage);
    void sacarPosicionable(Coordinates posicion);
    void sacarPosicionable(Coordinates posicion, const std::type_info& type_id);
    void sacarItem(Coordinates posicion, const std::type_info& type_id);
    void removePassage(Coordinates& position);
    Posicionable* obtenerPosicionableEn(Coordinates posicion) const;
    Objeto* getNearestPassage(Coordinates& position);
    Puerta* getDoor(Coordinates& position);    
    void moveme(Player* jugador, const Coordinates& posicion);
//    Mapa(const Mapa&) = delete;
    Mapa(Mapa&& other);
//    Mapa& operator=(const Mapa&) = delete;
    Mapa& operator=(Mapa&& other);
    
    bool hayObstaculoEn(const Coordinates& posicion) const;
    bool hayObstaculoEn(float x, float y) const;
    bool playerIn(const Coordinates& posicion) const;
    bool hayPuertaEn(float x, float y) const;
    int getAlto() const;
    int getAncho() const;
    ~Mapa();
};

#endif
