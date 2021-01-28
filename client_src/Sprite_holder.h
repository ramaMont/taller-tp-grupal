#ifndef __SPRITE_HOLDER__
#define __SPRITE_HOLDER__

#include <iostream>
#include <vector>

class Raycasting;
#include "ray_casting.h"

#include <Jugador.h>
#include <Character.h>

#include <Posicionable.h>

#include <Sprite_drawer.h>

//Puede tener más de un sprite y además un enemigo
class Sprite_holder : public Posicionable, public Sprite_drawer{
protected:
	std::vector<int> sprites_textures;
    Character* character;
    bool colidable;

public:
    explicit Sprite_holder(Coordinates posicion, int texture, Jugador &player);

    void is_colidable();

    void add_sprite(int num_texture);

    void colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

	void spotted();

    void add(Character* character) override;

    void remove() override;

    void draw(const std::vector<float> &distances, int n_rays) override;

};

#endif
