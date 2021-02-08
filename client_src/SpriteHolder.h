#ifndef __SPRITE_HOLDER__
#define __SPRITE_HOLDER__

#include <iostream>
#include <vector>

class Raycasting;
#include "rayCasting.h"

#include <Player.h>
#include <Movable.h>

#include <Posicionable.h>

#include <SpriteDrawer.h>

//Almacena multiples texturas de sprites y, en algunos casos, un personaje
class SpriteHolder : public Posicionable, public SpriteDrawer{
protected:
	std::vector<int> sprites_textures;
    Movable* character;
    bool colidable;

public:
    explicit SpriteHolder(Coordinates posicion, int texture, Player &player);

    //Pre:-
    // Setea al sprite como "colisionable", de manera que no pueda ser atravesado por los personajes
    void isColidable();

    //Pre:-
    // Agrega otra textura de sprite a dibujar
    void addSprite(int num_texture);

    //Pre:-
    // Le indica al rayo que colisionó con un sprite
    void colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

    //Pre:-
    // Setea al sprite como avistado
	void spotted();

    //Pre:-
    // devuelve si está almacenando o no un personaje
    bool hasCharacter();

    //Pre:-
    // Devuelve el puntero al personaje
    Movable* getCharacter();

    //Pre:-
    // Agrega un personaje
    void add(Movable* character) override;

    //Pre:-
    // remueve al personaje
    void remove() override;

    //Pre:-
    // Llamo a su dibujador de texturas
    void callDrawer(int first_sigted_ray,int first_num_pixel,int last_sigted_ray,int last_num_pixel,float player_distance) override;

};

#endif
