#ifndef __SPRITE_HOLDER__
#define __SPRITE_HOLDER__

#include <iostream>
#include <vector>

class Raycasting;
#include "rayCasting.h"

#include <Player.h>
#include <Character.h>

#include <Posicionable.h>

#include <SpriteDrawer.h>

//Almacena multiples texturas de sprites y, en algunos casos, un personaje
class SpriteHolder : public Posicionable, public SpriteDrawer{
protected:
	std::vector<int> sprites_textures;
    Character* character;
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
    Character* getCharacter();

    //Pre:-
    // Agrega un personaje
    void add(Character* character) override;

    //Pre:-
    // remueve al personaje
    void remove() override;

    //Pre:-
    // Llamo a su dibujador de texturas
    void draw(const std::vector<float> &distances, int n_rays) override;

};

#endif
