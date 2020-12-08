#ifndef SPRITE_H
#define SPRITE_H

#include "stdio.h"

#include <math.h>
#include <string>
#include <vector>

#include "camera.h"

#include <coordinates.h>
#include <Barrel.h>


class Sprite {

	private:

		Barrel* barrel;
		Coordinates position;
		float lowest_ray_distance;
		int num_closest_ray;

		float player_distance;
		int cant_rays;

	public:
		Sprite(Barrel *barrel){
			this->barrel = barrel;
			position = barrel->getPosicion();
			lowest_ray_distance = 90;
		}

		float dist(Coordinates ray_direction, Coordinates player_position){
			float num = ray_direction.x*(position.x - player_position.x) + ray_direction.y*(position.y - player_position.y);
			float denom = ray_direction.x*ray_direction.x + ray_direction.y*ray_direction.y;
			float n = num/denom;

			Coordinates colision_line = player_position;
			colision_line.x+=n*ray_direction.x;
			colision_line.y+=n*ray_direction.y;

			return sqrt(pow(colision_line.x - position.x,2) + pow(colision_line.y - position.y,2));
		}

		void update_distance_to_closest_ray(int i,Coordinates ray_direction, Coordinates player_position){
			Coordinates object_direction;
			object_direction.x = position.x - player_position.x;
			object_direction.y = position.y - player_position.y;
			object_direction.normalice_direction();
			ray_direction.normalice_direction();
			float distance = sqrt(pow(object_direction.x - ray_direction.x,2) + pow(object_direction.y - ray_direction.y,2));
			if(distance<lowest_ray_distance){
				lowest_ray_distance = distance;
				num_closest_ray = i;
			}
		}

		/*void set_center_ray(Coordinates player_position,Camera camera){
			Coordinates object_direction;
			object_direction.x = position.x - player_position.x;
			object_direction.y = position.y - player_position.y;
			object_direction.normalice_direction();
			num_closest_ray = camera.calculate_num_ray(object_direction);
		}*/

		void set_distance(Coordinates player_position, Coordinates camera_plane){
			player_distance = dist(camera_plane,player_position);//std::abs(player_position.y - position.y);
			if(player_distance<0.5)
				player_distance=0.5;

			cant_rays = 180/player_distance;
		}

		float get_distance_player_plane(){
			return player_distance;
		}

		int get_cant_rays(){
			return cant_rays;
		}

		int get_texture(){
			return barrel->get_texture();
		}

		int get_centered_ray(){
			return num_closest_ray;
		}

};
#endif
