#include "SpriteDrawer.h"

#include <vector> 

SpriteDrawer::SpriteDrawer(Posicionable *posicionable, Player &player): 
posicionable(posicionable), player(player) {
	located = false;
	player_distance = 0;
	relative_angle_to_player = 0;
	lowest_ray_distance = 0;
	center_ray = 0;
	cant_rays = 0;
}   

void SpriteDrawer::setRelativeAngleToPlayer(){
    Coordinates player_position = player.get_position();
    Coordinates player_direction = player.getDirection();

    Coordinates sprite_position = posicionable->get_position();

	Coordinates relative_player_pos;
	relative_player_pos.x = sprite_position.x - player_position.x;
	relative_player_pos.y = sprite_position.y - player_position.y;

	double dist = player_direction.x*relative_player_pos.x;
	dist += player_direction.y*relative_player_pos.y;
	double det = player_direction.x*relative_player_pos.y;
	det -= player_direction.y*relative_player_pos.x;

	relative_angle_to_player = atan2(det, dist);
}

void SpriteDrawer::updateDistanceToClosestRay(int i,int n_rays){
	double ray_angle = atan(((double)i/(double)n_rays));
	double distance = std::abs(relative_angle_to_player + ray_angle);
	if(distance<lowest_ray_distance){
		lowest_ray_distance = distance;
		center_ray = i;
	}
}


void SpriteDrawer::setDistance(int half_pixels,Coordinates camera_plane){
	Coordinates pos = posicionable->get_position();
	Coordinates player_pos = player.get_position();
	player_distance = pos.calculate_distance_to_vector(camera_plane,
																player_pos);
	if(player_distance<0.5)
		player_distance=0.5;
	//360 si tengo 640 de resolucion, 180 si tengo 320-> resolucion/2?
	cant_rays = half_pixels/player_distance;
}

void SpriteDrawer::spottedSprite(){
	located = true;
} 	

bool SpriteDrawer::isSpotted(){
	return located;
}

void SpriteDrawer::disableSpotted(){
	located = false;
	player_distance = 90;
	lowest_ray_distance = 90;
}

void SpriteDrawer::draw(const std::vector<float> &distances, int n_rays){
	int first_ray = center_ray - cant_rays/2;
	bool first_ray_already_sigted = false;
	int first_sigted_ray = 0;
	int first_num_pixel = 0;
	int last_sigted_ray = 0;
	int last_num_pixel = 0;

	int cant_spotted_rays = 0;
	for(int i=0 ; i<cant_rays ; i++){
		int num_pixel = i*64/cant_rays;
		int current_ray = first_ray + i+ n_rays;
		if((current_ray)>0 and(current_ray)<2*n_rays){
			if(distances[current_ray]>player_distance){
				cant_spotted_rays++;
				if(first_ray_already_sigted){
					last_sigted_ray = first_ray + i + n_rays;
					last_num_pixel = num_pixel;
				}else{
					first_sigted_ray = first_ray + i + n_rays;
					first_num_pixel = num_pixel;
				}
				first_ray_already_sigted = true;
			}
		}
	}

	if(cant_spotted_rays==1){
		last_sigted_ray = first_sigted_ray;
		last_num_pixel = first_num_pixel;
	}

	callDrawer(first_sigted_ray,first_num_pixel,
		last_sigted_ray,last_num_pixel,player_distance);
}

float SpriteDrawer::getDistancePlayerPlane() const {
	return player_distance;
}	
