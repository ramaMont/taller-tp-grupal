#include "Sprite_drawer.h"

float Sprite_drawer::dist(Coordinates ray_direction, Coordinates player_position){
	float num = ray_direction.x*(sprite_position.x - player_position.x) + ray_direction.y*(sprite_position.y - player_position.y);
	float denom = ray_direction.x*ray_direction.x + ray_direction.y*ray_direction.y;
	float n = num/denom;

	Coordinates colision_line = player_position;
	colision_line.x+=n*ray_direction.x;
	colision_line.y+=n*ray_direction.y;

	return sqrt(pow(colision_line.x - sprite_position.x,2) + pow(colision_line.y - sprite_position.y,2));
}