#include "ray.h"

Ray::Ray(const float &ray_angle,const Coordinates &ray_direction,\
	const Coordinates &player_position,const Coordinates &player_direction,\
	const std::vector<std::vector<int>> &map):
	ray_direction(ray_direction), 
	player_position(player_position), 
	player_direction(player_direction), map(map), 
	direction_relative_to_player(ray_angle)  {}


bool Ray::es_entero(const float &number){
	return( (number == floor(number)) and (number == ceil(number)));
}

int Ray::get_increase(const float &direction){
	int increase = 0;
	if(direction<=0){
		increase = -1;
	}
	return increase;
}

bool Ray::has_element(const Coordinates &map_coordinates){
	bool has_element = false;
	int aumento_x = get_increase(ray_direction.x);
	int aumento_y = get_increase(ray_direction.y);

	if(es_entero(map_coordinates.x) and es_entero(map_coordinates.y)){
		has_element = map[(int)map_coordinates.y+aumento_y][(int)map_coordinates.x+aumento_x]!=0;
	}else if(es_entero(map_coordinates.x)){
		has_element = map[(int)map_coordinates.y][(int)map_coordinates.x+aumento_x]!=0;
	}else{
		has_element = map[(int)map_coordinates.y+aumento_y][(int)map_coordinates.x]!=0;
	}
	return has_element;
}

float Ray::get_distance_to_player_plane(const Coordinates &object_coordinates,const bool &first_triangle){
	float distance;
	float hip = sqrt(pow(std::abs(player_position.x-object_coordinates.x),2) + pow(std::abs(player_position.y-object_coordinates.y),2));
	if(first_triangle){
		distance = cos(direction_relative_to_player)*hip;
	}else{
		distance = sin((PI/2 - direction_relative_to_player))*hip;
	}
	return(distance);
}

float Ray::search_ray_distance(const Coordinates &coordinatess){
	float x_distance;
	if(ray_direction.x>0){ //La direccion de mi rayo influye en qué pared tengo que mirar, ya que siempre estoy entre 2
		x_distance = floor(coordinatess.x+1) - coordinatess.x;
	}else{
	    x_distance = ceil(coordinatess.x-1) - coordinatess.x;
	}
	float y_height = x_distance * (ray_direction.y/ray_direction.x);
	float y_distance;
	if(ray_direction.y>0){
        y_distance = floor(coordinatess.y+1) - coordinatess.y;
	}else{
	    y_distance = ceil(coordinatess.y-1) - coordinatess.y;
	}
	float x_height = y_distance * tan(PI/2 - atan((ray_direction.y/ray_direction.x)));

	Coordinates coordinates_map;
	if(std::abs(x_distance*y_height) < std::abs(y_distance*x_height)){
		coordinates_map.x=coordinatess.x + x_distance;
		coordinates_map.y=coordinatess.y + y_height;
		if(has_element(coordinates_map)){
			float distance_player_plane = get_distance_to_player_plane(coordinates_map,true);
			return distance_player_plane;
		}else{
			return search_ray_distance(coordinates_map);
		}
	}else{//El segundo triangulo es menor
		coordinates_map.x=coordinatess.x + x_height;
		coordinates_map.y=coordinatess.y + y_distance;
		if(has_element(coordinates_map)){
			float distance_player_plane = get_distance_to_player_plane(coordinates_map,false);
			return distance_player_plane;
		}else{
			return search_ray_distance(coordinates_map);
		}
	}
}

float Ray::calculate_ray_distance(){
	return search_ray_distance(player_position);
}
