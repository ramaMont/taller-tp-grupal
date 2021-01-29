#include "Sprite_drawer.h"

Sprite_drawer::Sprite_drawer(Posicionable *posicionable, Player &player): 
posicionable(posicionable), player(player) {}   

void Sprite_drawer::set_relative_angle_to_player(){
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

void Sprite_drawer::update_distance_to_closest_ray(int i,int n_rays){
	double ray_angle = atan(((double)i/(double)n_rays));
	double distance = std::abs(relative_angle_to_player + ray_angle);
	if(distance<lowest_ray_distance){
		lowest_ray_distance = distance;
		center_ray = i;
	}
}


void Sprite_drawer::set_distance(int half_pixels,Coordinates camera_plane){
	player_distance = (posicionable->get_position()).calculate_distance_to_vector(camera_plane,player.get_position());
	if(player_distance<0.5)
		player_distance=0.5;
	//360 si tengo 640 de resolucion, 180 si tengo 320-> resolucion/2?
	cant_rays = half_pixels/player_distance; //La cantidad de rayos es irrelevante al tema de la "vibracion" de los sprites
}

void Sprite_drawer::spotted_sprite(){
	located = true;
} 	

bool Sprite_drawer::is_spotted(){
	return located;
}

void Sprite_drawer::disable_spotted(){
	located = false;
	player_distance = 90;
	lowest_ray_distance = 90;
}

float Sprite_drawer::get_distance_player_plane() const {
	return player_distance;
}		    
