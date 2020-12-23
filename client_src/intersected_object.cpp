#include "intersected_object.h"

#include <cmath>

Intersected_object::Intersected_object(float distance_player_plane, 
        float position, int side){
    distance = distance_player_plane;
    number_line_texture = floor((position - floor(position))*64);
    side_division = side;
}

float Intersected_object::get_distance_player_plane(){
	return distance;
}

int Intersected_object::get_number_line_texture(){
	return number_line_texture;
}

int Intersected_object::get_side_division(){
    return side_division;
}

