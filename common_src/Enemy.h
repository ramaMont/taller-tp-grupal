#ifndef __ENEMY__
#define __ENEMY__

#include "Posicionable.h"

#include "coordinates.h"
class Mapa;
#include "Mapa.h"
class Direccion;
#include "Direccion.h"

class Movable;
#include <Movable.h>

class Drawer;

#include "Sprite_drawer.h"

class Enemy : public Movable, public Sprite_drawer{
private:
	Jugador &player;	
	int num_texture;
	std::string id;

public:
	explicit Enemy(Coordinates posicion, int num_texture, Coordinates direction ,Mapa& mapa, Jugador &player ,std::string id);

    Intersected_object colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
        spotted();
        return ray->sprite_colided(coordinates_map);
    } 

	void spotted() override{
		spotted_sprite();
	}


	void draw(Drawer &drawer,  const std::vector<float> &distances, int n_rays);

};

#endif
