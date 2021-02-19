#include <math.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "rayCasting.h"
#include "ray.h"

Raycasting::Raycasting(Player &a_player,ClientMap &a_map, int n_rays)
    : player(a_player), map(a_map),n_rays(n_rays){}

void Raycasting::calculateRayCasting(Camera &camera,\
							std::vector<float> &distances){
    Coordinates player_position = player.get_position();
    Coordinates player_direction = player.getDirection();
	for(int i=-n_rays; i<=n_rays; i++){
		Coordinates ray_direction = camera.calculateRayDirection(i,n_rays);
		float ray_angle = atan(std::abs((float)i/(float)n_rays));
		Ray ray(ray_angle, ray_direction,distances,
				player_position,player_direction,map,i,n_rays, player.hasLivesLeft());
		ray.drawRay();
	}
}
