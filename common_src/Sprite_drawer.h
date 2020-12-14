#ifndef __SPRITE_DRAWER__
#define __SPRITE_DRAWER__

#include <iostream>
#include <vector>

class Raycasting;
#include "ray_casting.h"

class Drawer;
#include "Drawer.h"

#include <coordinates.h>

//Puede tener más de un sprite y además un enemigo
class Sprite_drawer{
protected:
	Coordinates sprite_position;
	int num_texture;
	Jugador &player;
	bool located;
	float player_distance;
	float lowest_ray_distance;
	int center_ray;
	int cant_rays;

	float dist(Coordinates ray_direction, Coordinates player_position);	

public:
    explicit Sprite_drawer(Coordinates posicion, int texture, Jugador &player): 
    sprite_position(posicion), num_texture(texture), player(player) {}   

    void update_position(Coordinates new_position){
    	sprite_position = new_position;
    }

    virtual void draw(Drawer &drawer,  const std::vector<float> distances, int n_rays)  = 0;

	void update_distance_to_closest_ray(int i,Coordinates ray_direction){
		Coordinates object_direction;
		Coordinates player_position = player.get_coordinates();
		object_direction.x = sprite_position.x - player_position.x;
		object_direction.y = sprite_position.y - player_position.y;
		object_direction.normalice_direction();
		ray_direction.normalice_direction();
		float distance = sqrt(pow(object_direction.x - ray_direction.x,2) + pow(object_direction.y - ray_direction.y,2));
		if(distance<lowest_ray_distance){
			lowest_ray_distance = distance;
			center_ray = i;
		}
	}

	void set_distance(Coordinates camera_plane){
		player_distance = dist(camera_plane,player.get_coordinates());//std::abs(player_position.y - position.y);
		if(player_distance<0.5)
			player_distance=0.5;
		cant_rays = 180/player_distance;
	}

	void spotted_sprite(){
		located = true;
	} 	

	bool is_spotted(){
		return located;
	}

	void disable_spotted(){
		located = false;
		player_distance = 90;
		lowest_ray_distance = 90;
	}

	float get_distance_player_plane() const{
		return player_distance;
	}		    

};

#endif
