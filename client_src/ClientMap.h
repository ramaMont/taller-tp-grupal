#ifndef __CLIENT_MAP__
#define __CLIENT_MAP__

#include <vector>
#include <utility>

class Posicionable;
//#include "Posicionable.h"
class Character;
class Movable;
class Player;
//#include "Player.h"
class Enemy;
#include <coordinates.h>


//Mapa del cliente
class ClientMap{
private:
    int alto;
    int ancho;
    std::vector<std::vector<Posicionable*>> mapGame;
    Character* player;

public:
    //TODO: Inicializar player en el constructor
    ClientMap();
    explicit ClientMap(int alto, int ancho);

    //Pre:-
    // Agrega al jugador (como un personaje común)
    void addPlayer(Character* _player);

    //Pre:-
    // Agrega al resto de posicionables al mapa    
    void addPositionable(Posicionable* positionable, Coordinates position);

    /*Pre:-
    Asigna una nueva posicion a un movible, se diferencia de addPositionable 
    porque, en caso de que la posicion esté ocupada, intenta agregarlo igual
    en caso de que en esa posicion haya un sprite o una puerta abierta*/
    void addMovable(Movable* _character, Coordinates posicion);


    //Pre:-
    // Remueve todo lo que hay en una posicion.
    void removePositionable(Coordinates position);

    //Pre:-
    // Remueve a un personaje de su posicion
    void removeMovable(Coordinates position);


    //Pre:-
    // Remueve un sprite donde actualmente se encuentra un personaje,
    // y deja al personaje en el mismo lugar    
    void removeSpriteWithCharacter(Coordinates position, Movable* character);

    //Pre:-
    // Devuelve el puntero al objeto almacenado en cierta posicion    
    Posicionable* getPositionableIn(Coordinates position);

    //Pre:-
    // Mueve al jugador (llama al addMovable y al removeMovable)    
    void moveme(Movable* character, const Coordinates& position);

    //Pre:-
    // Modifica el ancho y el alto del mapa    
    void resize(int ancho, int alto);

    bool isInside(const Coordinates& coordinates);

    ~ClientMap();
};

#endif
