#include "Rocket.h"

#include <math.h>

Rocket::Rocket(Coordinates posicion,Coordinates direction,\
                    ClientMap& map, Player &player, int rocket_id):
    Movable(posicion,direction,map),SpriteDrawer(this,player),
    rocket_id(rocket_id){	
}


void Rocket::colisioned(Ray* ray,Coordinates coordinates_map,bool first_tr){
    spottedSprite();
    ray->spriteColided(coordinates_map);
}

#define ROCKET_STEP 0.25

void Rocket::move(){
	Coordinates nuevaPos = posicion;
	nuevaPos.increment_on_direction(direction,ROCKET_STEP);
    try{
        map.moveme(this, nuevaPos);
        this->posicion = nuevaPos;
    } catch(...){
    }
}

void Rocket::callDrawer(int first_sigted_ray,int first_num_pixel,\
				int last_sigted_ray,int last_num_pixel,float player_distance){
	texture_drawer->showSprite(first_sigted_ray,first_num_pixel,
				last_sigted_ray,last_num_pixel,player_distance ,12);
}

int Rocket::getRocketId(){
    return rocket_id;
}

Rocket::~Rocket(){
}
