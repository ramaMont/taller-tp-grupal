#include <math.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "ray_casting.h"
#include "ray.h"

Raycasting::Raycasting(Player &a_player,ClMap &a_map, int n_rays)
    : player(a_player), map(a_map),n_rays(n_rays){}




void Raycasting::calculate_raycasting(Camera &camera,std::vector<float> &distances){

	//Desactivo todos los sprites que fueron vistos el anterior frame
    Coordinates player_position = player.get_position();
    Coordinates player_direction = player.get_direction();
	for(int i=-n_rays; i<=n_rays; i++){
		Coordinates ray_direction = camera.calculate_ray_direction(i,n_rays);
		float ray_angle = atan(std::abs((float)i/(float)n_rays));
		Ray ray(ray_angle, ray_direction,distances,player_position,player_direction,map,i,n_rays);
		ray.draw_ray();
	}


}