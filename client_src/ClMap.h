#ifndef __CL_MAPA__
#define __CL_MAPA__

#include <vector>
#include <utility>
class Posicionable;
//#include "Posicionable.h"
class Character;
class Movable;
class Player;
//#include "Player.h"
class Enemy;
#include "coordinates.h"


//Mapa del cliente
class ClMap{
private:
    int alto;
    int ancho;
    std::vector<std::vector<Posicionable*>> mapGame;
    Character* player;
public:
    ClMap();
    explicit ClMap(int alto, int ancho);

    //Pre:-
    // Agrega al jugador (como un personaje común)
    void addPlayer(Character* _player);

    //Pre:-
    // Agrega al resto de posicionables al mapa    
    void addPositionable(Posicionable* positionable, Coordinates position);

    //Pre:-
    // Asigna una nueva posicion al personaje
    void relocate(Movable* _character, Coordinates posicion);

    //Pre:-
    // Remueve a un personaje de su posicion
    void removePositionable(Coordinates position);

    //Pre:-
    // Remueve todos los punteros de su posicion
    void removeAllPositionables(Coordinates position);

    //Pre:-
    // Remueve un sprite donde actualmente se encuentra un personaje, y deja al personaje en el mismo lugar    
    void removeSpriteWithCharacter(Coordinates position, Movable* character);

    //Pre:-
    // Devuelve el puntero al objeto almacenado en cierta posicion    
    Posicionable* getPositionableIn(Coordinates position);

    //Pre:-
    // Mueve al jugador (llama al relocate y al removePositionable)    
    void moveme(Movable* character, const Coordinates& position);

    //Pre:-
    // Modifica el ancho y el alto del mapa    
    void resize(int ancho, int alto);

    ~ClMap();
};

#endif
