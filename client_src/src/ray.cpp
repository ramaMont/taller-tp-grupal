#include "ray.h"

Ray::Ray(const float &ray_angle,const Coordinates &ray_direction,\
	const Coordinates &player_position,const Coordinates &player_direction,\
	const std::vector<std::vector<int>> &map):
	ray_direction(ray_direction), 
	player_position(player_position), 
	player_direction(player_direction), map(map), 
	direction_relative_to_player(ray_angle)  {}


bool Ray::has_element(const Coordinates &map_coordinates){
	int aumento_x = ray_direction.get_increase_x();
	int aumento_y = ray_direction.get_increase_y();

	Coordinates whole_coordinates = map_coordinates;

	if(map_coordinates.x_whole() and map_coordinates.y_whole()){
		whole_coordinates.inc_x(aumento_x);
		whole_coordinates.inc_y(aumento_y);
	}else if(map_coordinates.x_whole()){
		whole_coordinates.inc_x(aumento_x);
	}else{ //Por descarte: y_whole()
		whole_coordinates.inc_y(aumento_y);
	}
	return whole_coordinates.has_element(map);
}

float Ray::get_distance_to_player_plane(const Coordinates &object_coordinates,const bool &first_triangle){
	float distance;
	float hip = object_coordinates.calculate_distance(player_position);
	if(first_triangle){
		distance = cos(direction_relative_to_player)*hip;
	}else{
		distance = sin((PI/2 - direction_relative_to_player))*hip;
	}
	return(distance);
}

float Ray::get_x_distance_to_side(const Coordinates &ray_position){
	if(ray_direction.x_positive()){ //La direccion de mi rayo influye en qué pared tengo que mirar, ya que siempre estoy entre 2
		return ray_position.get_distance_to_lower_side_x();
	}else{
	    return ray_position.get_distance_to_higher_side_x();
	}
}

float Ray::get_y_distance_to_side(const Coordinates &ray_position){
	if(ray_direction.y_positive()){ //La direccion de mi rayo influye en qué pared tengo que mirar, ya que siempre estoy entre 2
		return ray_position.get_distance_to_lower_side_y();
	}else{
	    return ray_position.get_distance_to_higher_side_y();
	}
}




float Ray::search_ray_distance(Coordinates ray_position){
	bool first_triangle = false; //qué triangulo use despues me afecta en calcular la distancia y el ángulo

	float x_distance = get_x_distance_to_side(ray_position);
	float y_height = x_distance * (ray_direction.y/ray_direction.x);

	float y_distance  = get_y_distance_to_side(ray_position);
	float x_height = y_distance * tan(PI/2 - atan((ray_direction.y/ray_direction.x)));

	Coordinates coordinates_map;
	if(std::abs(x_distance*y_height) < std::abs(y_distance*x_height)){
		coordinates_map.x=ray_position.x + x_distance;
		coordinates_map.y=ray_position.y + y_height;
		first_triangle = true;
	}else{//El segundo triangulo es menor
		coordinates_map.x=ray_position.x + x_height;
		coordinates_map.y=ray_position.y + y_distance;
		first_triangle = false;
	}
	if(has_element(coordinates_map)){
		float distance_player_plane = get_distance_to_player_plane(coordinates_map,first_triangle);
		return distance_player_plane;
	}else{
		return search_ray_distance(coordinates_map);
	}	
}

float Ray::calculate_ray_distance(){
	return search_ray_distance(player_position);
}
