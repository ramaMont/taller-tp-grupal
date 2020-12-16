#ifndef __WALL__
#define __WALL__

#include "Posicionable.h"

class Wall final : public Posicionable{

public:
    explicit Wall(Coordinates posicion, int num_texture): 
    Posicionable(posicion,num_texture){}

	Intersected_object colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
		return ray->wall_colided(coordinates_map,first_triangle,this);
	}

};

#endif
