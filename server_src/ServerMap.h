#ifndef __SERVER_MAP__
#define __SERVER_MAP__

#include <coordinates.h>
#include <Posicionable.h>
#include "Player.h"
class Player;
#include "Item.h"
class Item;
class Object;
class Door;
#include "Object.h"


#include <yaml-cpp/yaml.h>
#include <map>
#include <tuple>
#include <vector>
#include <utility>

class ServerMap{
private:
    int alto;
    int ancho;
    std::vector<std::vector<std::vector<Posicionable*>>> mapaJuego;
    std::vector<std::vector<Item*>> items;
    std::vector<Object*> passages;
    std::vector<std::tuple<Coordinates, std::string>> player_positions;
    int players_added;
    void initMap(ServerMap& map, YAML::Node map_node);
    void initItems();

public:
    explicit ServerMap(std::string map_filename);
    explicit ServerMap(int alto, int ancho);
    
    // Agrega un jugador al mapa
    void addPlayer(Player* player);
    
    // Reestablece al jugador en su posicion
    void respawnPlayer(Player* player);
    
    // Agrga un objeto en la posicion indicada
    void addPosicionable(Posicionable* posicionable, Coordinates posicion);
    
    // Agrega un item al mapa
    void addItem(Item* item, Coordinates posicion);
    
    // Agrega un pasaje al mapa
    void addPassage(Object* passage);
    
    // Elimina el ultimo objeto agregado el la posicion del mapa
    void removePosicionable(const Coordinates& posicion);
    
    // Elimina el item de la posicion
    void removeItem(const Coordinates& posicion);
    
    // Elimina el pasaje de la posicion
    void removePassage(const Coordinates& position);
    
    // Retorna el ultimo posicionable agregado en la posicion
    Posicionable* getPosicionableIn(Coordinates posicion) const;
    
    // Retorna el pasaje mas cercano a la posicion
    Object* getNearestPassage(Coordinates& position);
    
    // Retorna la puerta ubicada en la posicion 
    Door* getDoor(Coordinates& position);
    
    // Mueve al jugador de una posicion del mapa a otra
    void moveme(Player* player, const Coordinates& posicion);
    
//    ServerMap(const ServerMap&) = delete;
    ServerMap(ServerMap&& other);
//    ServerMap& operator=(const ServerMap&) = delete;
    ServerMap& operator=(ServerMap&& other);
    
    // Retorna la posicion vacia del mapa mas cercana a 'posicion'
    Coordinates getEmptyPosition(const Coordinates& posicion);
    
    // Retorna true si en la posicion hay un objeto que impida cruzarlo
    bool obstacleIn(const Coordinates& posicion) const;
    
    // Retorna true si en la posicion hay un jugador
    bool playerIn(const Coordinates& posicion) const;
    
    // Retorna true si en la posicion hay una puerta
    
    // Retorna true si en la posicion x,y hay una puerta
    bool doorIn(float x, float y) const;
    
    // Retorna el alto del mapa
    int getAlto() const;
    
    // Retorna el ancho del mapa
    int getAncho() const;
    ~ServerMap();
};

#endif
