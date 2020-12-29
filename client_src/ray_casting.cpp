#include <math.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "ray_casting.h"
#include "ray.h"

Raycasting::Raycasting(Jugador &a_player,Cl_Mapa &a_map, int n_rays)
    : player(a_player), map(a_map),n_rays(n_rays){}




void Raycasting::calculate_raycasting(Camera &camera,std::vector<float> &distances){

	//Desactivo todos los sprites que fueron vistos el anterior frame
    Coordinates player_position = player.get_position();
    Coordinates player_direction = player.get_direction();
	for(int i=-n_rays; i<=n_rays; i++){
		Coordinates ray_direction = camera.calculate_ray_direction(i,n_rays);
		float ray_angle = atan(std::abs((float)i/(float)n_rays));
		Ray ray(ray_angle, ray_direction,distances,player_position,player_direction,map,i);
		Intersected_object intersected_object = ray.get_colisioned_objects();
		intersected_object.draw(i+n_rays);
		/*float distance_player_plane = intersected_object.get_distance_player_plane();
		int number_line_texture = intersected_object.get_number_line_texture();
		int texture = intersected_object.get_texture();
		bool wall_side_y = intersected_object.get_side_wall_colided();
		texture_drawer.show_wall(i,distance_player_plane,number_line_texture,texture, wall_side_y);*/
	}


}