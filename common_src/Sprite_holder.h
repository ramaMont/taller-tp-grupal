#ifndef __SPRITE_HOLDER__
#define __SPRITE_HOLDER__

#include <iostream>
#include <vector>

class Raycasting;
#include "ray_casting.h"

#include <Jugador.h>
#include <Movable.h>

#include "Posicionable.h"

#include <Sprite_drawer.h>

//Puede tener más de un sprite y además un enemigo
class Sprite_holder : public Posicionable, public Sprite_drawer{
protected:
	std::vector<int> sprites_textures;
    Movable* movable;

public:
    explicit Sprite_holder(Texture &texture_drawer, Coordinates posicion, int texture, Jugador &player): 
    Posicionable(texture_drawer,posicion,texture),Sprite_drawer(this,player) ,movable(nullptr){
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

    void draw(const std::vector<float> &distances, int n_rays) override;

};

#endif
