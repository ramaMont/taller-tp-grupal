#ifndef __MAPA__
#define __MAPA__

#include <vector>
#include <utility>
#include "Posicionable.h"
#include "Player.h"
class Player;
#include "Item.h"
class Object;
class Door;
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
    std::vector<Object*> passages;
    std::vector<std::tuple<Coordinates, std::string>> player_positions;
    int players_added;
    void initMap(Mapa& map, YAML::Node map_node);


public:
    explicit Mapa(std::string map_filename);
    explicit Mapa(int alto, int ancho);
    void addPlayer(Player* player);
    void respawnPlayer(Player* player);
    void addPosicionable(Posicionable* posicionable, Coordinates posicion);
    void addItem(Item* item, Coordinates posicion);
    Coordinates throwItem(Item* item, Coordinates posicion);
    void addPassage(Object* passage);
    void removePosicionable(Coordinates posicion);
    void removeItem(Coordinates posicion, const std::type_info& type_id);
    void removePassage(Coordinates& position);
    Posicionable* getPosicionableIn(Coordinates posicion) const;
    Object* getNearestPassage(Coordinates& position);
    Door* getDoor(Coordinates& position);    
    void moveme(Player* player, const Coordinates& posicion);
//    Mapa(const Mapa&) = delete;
    Mapa(Mapa&& other);
//    Mapa& operator=(const Mapa&) = delete;
    Mapa& operator=(Mapa&& other);
    
    bool obstacleIn(const Coordinates& posicion) const;
    bool playerIn(const Coordinates& posicion) const;
    bool doorIn(float x, float y) const;
    int getAlto() const;
    int getAncho() const;
    ~Mapa();
};

#endif
