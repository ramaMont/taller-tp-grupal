#include "intersected_object.h"

#include "texture.h"
#include <Wall.h>
#include <cmath>

Intersected_object::Intersected_object(float distance_player_plane,Wall* object ,float position, bool wall_side_y):
	number_line_texture(floor ((position - floor(position))*64)),
	distance(distance_player_plane),
	object(object),
	wall_side_y(wall_side_y) {}


void Intersected_object::draw(int x_pixel){
	object->draw(x_pixel,distance,number_line_texture,wall_side_y);
}

