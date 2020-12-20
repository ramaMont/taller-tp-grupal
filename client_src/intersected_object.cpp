#include "intersected_object.h"

#include <cmath>

Intersected_object::Intersected_object(float distance_player_plane,Posicionable* object ,float position, bool wall_side_y):
	number_line_texture(floor ((position - floor(position))*64)),
	distance(distance_player_plane),
	object(object),
	wall_side_y(wall_side_y) {}

float Intersected_object::get_distance_player_plane(){
	return distance;
}

int Intersected_object::get_texture(){
  	return object->get_texture();
}

int Intersected_object::get_number_line_texture(){
	return number_line_texture;
}

bool Intersected_object::get_side_wall_colided(){
    return wall_side_y;
}

