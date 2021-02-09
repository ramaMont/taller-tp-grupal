#include "Rocket.h"

#include <math.h>

/*static int get_num_texture(Coordinates enemy_position, Coordinates enemy_direction, Coordinates player_position){
	Coordinates relative_player_pos;
	relative_player_pos.x = player_position.x - enemy_position.x;
	relative_player_pos.y = player_position.y - enemy_position.y;


	float dist = enemy_direction.x*relative_player_pos.x + enemy_direction.y*relative_player_pos.y;
	float det = enemy_direction.x*relative_player_pos.y - enemy_direction.y*relative_player_pos.x;

	float angle = atan2(det, dist);
	float abs_angle = std::abs(angle);
	int side = 0;
	if(abs_angle<M_PI/8)
		side = 0;
	else if(abs_angle<3*M_PI/8){
		if(angle<0)
			side = 7;
		else
			side = 1;
	}
	else if(abs_angle<5*M_PI/8){
		if(angle<0)
			side = 6;
		else
			side = 2;
	}
	else if(abs_angle<7*M_PI/8){
		if(angle<0)
			side = 5;
		else
			side = 3;
	}
	else
		side = 4;
	return side;
}*/


Rocket::Rocket(Coordinates posicion, Coordinates direction,ClMap& map, Player &player):
    Movable(posicion,direction,map),SpriteDrawer(this,player),
   	player(player){	
    }


void Rocket::colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
    spottedSprite();
    ray->spriteColided(coordinates_map);
}

#define ROCKET_STEP 0.25

void Rocket::move(){
	Coordinates nuevaPos = posicion;
	nuevaPos.increment_on_direction(direction,ROCKET_STEP);
    //Coordinates nuevaPos = direccion->move(this,direction);
    try{
        map.moveme(this, nuevaPos);
        this->posicion = nuevaPos;
    } catch(...){
    }
}


void Rocket::callDrawer(int first_sigted_ray,int first_num_pixel,int last_sigted_ray,int last_num_pixel,float player_distance){
	texture_drawer->showSprite(first_sigted_ray,first_num_pixel,last_sigted_ray,last_num_pixel,player_distance ,12);
}


Rocket::~Rocket(){
}