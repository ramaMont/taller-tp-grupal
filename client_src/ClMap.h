#ifndef __CL_MAPA__
#define __CL_MAPA__

#include <vector>
#include <utility>
class Posicionable;
//#include "Posicionable.h"
class Character;
class Player;
//#include "Player.h"
class Enemy;
#include "coordinates.h"


class ClMap{
private:
    int alto;
    int ancho;
    std::vector<std::vector<Posicionable*>> mapGame;
    Character* player;
public:
    ClMap();
    explicit ClMap(int alto, int ancho);
    void addPlayer(Character* _player);
    void addPositionable(Posicionable* positionable, Coordinates position);
    void relocate(Character* jugador, Coordinates posicion);
    void removePositionable(Coordinates position);
    void removeSpriteWithCharacter(Coordinates position, Character* character);
    Posicionable* getPositionableIn(Coordinates position);
    void moveme(Character* character, const Coordinates& position);
    void resize(int ancho, int alto);

    ~ClMap();
};

#endif
