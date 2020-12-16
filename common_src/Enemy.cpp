#include "Enemy.h"

#include "Drawer.h"

#include <math.h>

Enemy::Enemy(Coordinates posicion, int num_texture, Coordinates direction ,Mapa& mapa, Jugador &player ,std::string id):
    Movable(posicion,direction,mapa),Sprite_drawer(this,player),player(player),num_texture(num_texture),id(id) {}


static int get_num_texture(Coordinates enemy_position, Coordinates enemy_direction, Coordinates player_position){
	Coordinates relative_player_pos;
	relative_player_pos.x = player_position.x - enemy_position.x;
	relative_player_pos.y = player_position.y - enemy_position.y;


	float dist = enemy_direction.x*relative_player_pos.x + enemy_direction.y*relative_player_pos.y;
	float det = enemy_direction.x*relative_player_pos.y - enemy_direction.y*relative_player_pos.x;

	float angle = atan2(det, dist);
	float abs_angle = std::abs(angle);
	int side = 0;
	if(abs_angle<M_PI/8)
		side = 0;
	else if(abs_angle<3*M_PI/8){
		if(angle<0)
			side = 1;
		else
			side = 7;

	}
	else if(abs_angle<5*M_PI/8){
		if(angle<0)
			side = 2;
		else
			side = 6;
	}
	else if(abs_angle<7*M_PI/8){
		if(angle<0)
			side = 3;
		else
			side = 5;
	}
	else
		side = 4;
	return side;
}

void Enemy::draw(Drawer &drawer, const std::vector<float> &distances, int n_rays){
	int first_ray = center_ray - cant_rays/2;
	int side_texture = get_num_texture(posicion,direction, player.get_position());
	for(int i=0 ; i<cant_rays ; i++){
		int num_pixel = i*64/cant_rays;
		if((first_ray + i+ n_rays)>0 and (first_ray + i+ n_rays)<2*n_rays){
			if(distances[first_ray + i+ n_rays]>player_distance){
				drawer.draw_guard(first_ray + i,player_distance ,num_pixel,side_texture);
			}
		}
	}
}