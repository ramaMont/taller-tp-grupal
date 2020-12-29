#ifndef __SPRITE_HOLDER__
#define __SPRITE_HOLDER__

#include <iostream>
#include <vector>

class Raycasting;
#include "ray_casting.h"

#include <Jugador.h>
#include <Movable.h>

#include "Cl_Posicionable.h"

#include <Sprite_drawer.h>

//Puede tener más de un sprite y además un enemigo
class Sprite_holder : public Cl_Posicionable, public Sprite_drawer{
protected:
	std::vector<int> sprites_textures;
    Movable* movable;

public:
    explicit Sprite_holder(Coordinates posicion, int texture, Jugador &player);

    void add_sprite(int num_texture);

    Intersected_object colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

	void spotted();

    void add(Movable* movable) override;

    void remove() override;

    void draw(const std::vector<float> &distances, int n_rays) override;

};

#endif
