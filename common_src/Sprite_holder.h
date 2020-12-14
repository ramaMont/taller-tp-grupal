#ifndef __SPRITE_HOLDER__
#define __SPRITE_HOLDER__

#include <iostream>
#include <vector>

class Raycasting;
#include "ray_casting.h"

class Drawer;
#include "Drawer.h"

#include <Movable.h>

#include "Posicionable.h"

#include <Sprite.h>
#include <Sprite_drawer.h>

//Puede tener más de un sprite y además un enemigo
class Sprite_holder : public Sprite, public Sprite_drawer{
protected:
	std::vector<int> sprites_textures;
    Movable* movable;

public:
    explicit Sprite_holder(Coordinates posicion, int texture, Jugador &player): 
    Sprite(posicion,texture,player),Sprite_drawer(posicion,texture,player) ,movable(nullptr){
    	sprites_textures.push_back(texture);
    }

    void add_sprite(int num_texture){
    	sprites_textures.push_back(num_texture);
    }

    Intersected_object colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
        spotted();
        return ray->sprite_colided(coordinates_map);
    }    

	void spotted(){
        spotted_sprite();
        if(movable!=nullptr){
            movable->spotted();
        }
	}    

    void add(Movable* movable) override;

    void remove() override;

    void draw(Drawer &drawer,  const std::vector<float> distances, int n_rays) override;

};

#endif
