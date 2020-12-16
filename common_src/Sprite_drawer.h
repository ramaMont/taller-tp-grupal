#ifndef __SPRITE_DRAWER__
#define __SPRITE_DRAWER__

#include <iostream>
#include <vector>

#include <math.h>

class Raycasting;
#include "ray_casting.h"

class Drawer;
#include "Drawer.h"

class Posicionable;
#include <Posicionable.h>

#include <coordinates.h>

//Puede tener más de un sprite y además un enemigo
class Sprite_drawer{
protected:
	Posicionable* posicionable;
	Jugador &player;
	bool located;
	float player_distance;
	double relative_angle_to_player;
	double lowest_ray_distance;
	int center_ray;
	int cant_rays;


public:
    explicit Sprite_drawer(Posicionable *posicionable, Jugador &player): 
    posicionable(posicionable), player(player) {}   


    virtual void draw(Drawer &drawer,  const std::vector<float> &distances, int n_rays)  = 0;

    void set_relative_angle_to_player(){
    	Coordinates player_position = player.get_position();
    	Coordinates player_direction = player.get_direction();

    	Coordinates sprite_position = posicionable->get_position();

		Coordinates relative_player_pos;
		relative_player_pos.x = sprite_position.x - player_position.x;
		relative_player_pos.y = sprite_position.y - player_position.y;


		double dist = player_direction.x*relative_player_pos.x + player_direction.y*relative_player_pos.y;
		double det = player_direction.x*relative_player_pos.y - player_direction.y*relative_player_pos.x;

		relative_angle_to_player = atan2(det, dist);
    }

	void update_distance_to_closest_ray(int i,int n_rays){
		double ray_angle = atan(((double)i/(double)n_rays));
		double distance = std::abs(relative_angle_to_player + ray_angle);
		if(distance<lowest_ray_distance){
			lowest_ray_distance = distance;
			center_ray = i;
		}
	}


	void set_distance(Coordinates camera_plane){
		player_distance = (posicionable->get_position()).calculate_distance_to_vector(camera_plane,player.get_position());
		if(player_distance<0.5)
			player_distance=0.5;
		cant_rays = 180/player_distance; //La cantidad de rayos es irrelevante al tema de la "vibracion" de los sprites
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
