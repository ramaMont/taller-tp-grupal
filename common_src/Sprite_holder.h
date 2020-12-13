#ifndef __SPRITE_HOLDER__
#define __SPRITE_HOLDER__

#include <iostream>
#include <vector>

class Raycasting;
#include "ray_casting.h"

class Drawer;
#include "Drawer.h"

#include <Jugador.h>

#include "Posicionable.h"

#include <Sprite.h>

//Puede tener más de un sprite y además un enemigo
class Sprite_holder : public Sprite{
protected:
	std::vector<int> sprites_textures;

public:
    explicit Sprite_holder(Coordinates posicion, int texture, Jugador &player): 
    Sprite(posicion,texture,player){
    	sprites_textures.push_back(texture);
    }

    void add_sprite(int num_texture){
    	sprites_textures.push_back(num_texture);
    }

    void draw(Drawer &drawer,  const std::vector<float> distances, int n_rays) override;

};

#endif
