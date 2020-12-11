#ifndef __SPRITE__
#define __SPRITE__

class Raycasting;
#include "ray_casting.h"

class Drawer;
#include "Drawer.h"

#include <Jugador.h>

#include "Posicionable.h"

class Sprite : public Posicionable{
protected:
	bool located;
	Jugador &player;
	float player_distance;
	float lowest_ray_distance;
	int center_ray;
	int cant_rays;

	float dist(Coordinates ray_direction, Coordinates player_position){
		float num = ray_direction.x*(posicion.x - player_position.x) + ray_direction.y*(posicion.y - player_position.y);
		float denom = ray_direction.x*ray_direction.x + ray_direction.y*ray_direction.y;
		float n = num/denom;

		Coordinates colision_line = player_position;
		colision_line.x+=n*ray_direction.x;
		colision_line.y+=n*ray_direction.y;

		return sqrt(pow(colision_line.x - posicion.x,2) + pow(colision_line.y - posicion.y,2));
	}

public:
    explicit Sprite(Coordinates posicion, int texture, Jugador &player): 
    Posicionable(posicion,texture),located(false),player(player){}

    virtual void draw(Drawer &drawer,  const std::vector<float> distances, int n_rays);

	Intersected_object colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
		located = true;
		return ray->sprite_colided(coordinates_map);
	}

	void update_distance_to_closest_ray(int i,Coordinates ray_direction){
		Coordinates object_direction;
		Coordinates player_position = player.get_coordinates();
		object_direction.x = posicion.x - player_position.x;
		object_direction.y = posicion.y - player_position.y;
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

	void spotted(){
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
