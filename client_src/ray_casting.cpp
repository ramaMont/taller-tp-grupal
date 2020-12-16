#include <math.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "ray_casting.h"
#include "ray.h"

Raycasting::Raycasting(Jugador &a_player,Mapa &a_map, int n_rays, Drawer &drawer)
    : player(a_player), map(a_map),n_rays(n_rays), drawer(drawer){}




void Raycasting::calculate_raycasting(Camera &camera,std::vector<float> &distances){

	//Desactivo todos los sprites que fueron vistos el anterior frame
    Coordinates player_position = player.get_position();
    Coordinates player_direction = player.get_direction();
	for(int i=-n_rays; i<=n_rays; i++){
		Coordinates ray_direction = camera.calculate_ray_direction(i,n_rays);
		float ray_angle = atan(std::abs((float)i/(float)n_rays));
		Ray ray(ray_angle, ray_direction,distances,player_position,player_direction,map,i);
		Intersected_object intersected_object = ray.get_colisioned_objects();
		float distance_player_plane = intersected_object.get_distance_player_plane();
		int number_line_texture = intersected_object.get_number_line_texture();
		int texture = intersected_object.get_texture();
		int side_division = intersected_object.get_side_division();
		drawer.draw_wall(i,distance_player_plane,number_line_texture,texture, side_division);
	}


}