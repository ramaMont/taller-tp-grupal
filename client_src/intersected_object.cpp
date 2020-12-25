#include "intersected_object.h"

#include <cmath>

Intersected_object::Intersected_object(float distance_player_plane,Posicionable* object ,float position, int side):
	number_line_texture(floor ((position - floor(position))*64)),
	distance(distance_player_plane),
	object(object),
	side_division(side) {}

float Intersected_object::get_distance_player_plane(){
	return distance;
}

int Intersected_object::get_number_line_texture(){
	return number_line_texture;
}

int Intersected_object::get_side_division(){
    return side_division;
}

