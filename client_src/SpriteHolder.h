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

//Puede tener más de un sprite y además un enemigo
class SpriteHolder : public Posicionable, public SpriteDrawer{
protected:
	std::vector<int> sprites_textures;
    Character* character;
    bool colidable;

public:
    explicit SpriteHolder(Coordinates posicion, int texture, Player &player);

    void isColidable();

    void addSprite(int num_texture);

    void colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

	void spotted();

    bool hasCharacter();

    Character* getCharacter();

    void add(Character* character) override;

    void remove() override;

    void draw(const std::vector<float> &distances, int n_rays) override;

};

#endif
