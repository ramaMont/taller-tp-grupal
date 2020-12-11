#include "ray.h"

static const int X_SIDE = 1;
static const int Y_SIDE = 2;

Ray::Ray(const double &ray_angle,const Coordinates &ray_direction,\
	std::vector<float> &distances,const Coordinates &player_position,const Coordinates &player_direction,\
	Mapa &map, int num_ray):
	player_direction(player_direction),
	player_position(player_position), 
	ray_direction(ray_direction), 
	direction_relative_to_player(ray_angle) ,
	distances(distances),
	map(map),
	num_ray(num_ray) {}

void Ray::increment_coordinates(Coordinates &whole_coordinates, int inc_x, int inc_y){
	if(whole_coordinates.x_whole() and whole_coordinates.y_whole()){
		whole_coordinates.inc_x(inc_x);
		whole_coordinates.inc_y(inc_y);
	}else if(whole_coordinates.x_whole()){
		whole_coordinates.inc_x(inc_x);
	}else{ //Por descarte: y_whole()
		whole_coordinates.inc_y(inc_y);
	}
}

Posicionable* Ray::get_element(Coordinates &map_coordinates){
	int inc_x = ray_direction.get_increase_x();
	int inc_y = ray_direction.get_increase_y();


	increment_coordinates(map_coordinates,inc_x,inc_y);

	map_coordinates.x = (int)map_coordinates.x;
	map_coordinates.y = (int)map_coordinates.y;

	return (map.obtenerPosicionableEn(map_coordinates));
}

double Ray::get_distance_to_player_plane(const Coordinates &object_coordinates,const bool &first_triangle){
	double distance;
	double hip = object_coordinates.calculate_distance(player_position);
	if(first_triangle){
		distance = cos(direction_relative_to_player)*hip;
	}else{
		distance = sin((M_PI/2 - direction_relative_to_player))*hip;
	}
	return(distance);
}

double Ray::get_x_distance_to_side(const Coordinates &ray_position){
	if(ray_direction.x_positive()){ //La direccion de mi rayo influye en qué pared tengo que mirar, ya que siempre estoy entre 2
		return ray_position.get_distance_to_lower_side_x();
	}else{
	    return ray_position.get_distance_to_higher_side_x();
	}
}

double Ray::get_y_distance_to_side(const Coordinates &ray_position){
	if(ray_direction.y_positive()){ //La direccion de mi rayo influye en qué pared tengo que mirar, ya que siempre estoy entre 2
		return ray_position.get_distance_to_lower_side_y();
	}else{
	    return ray_position.get_distance_to_higher_side_y();
	}
}

Intersected_object Ray::get_wall(Coordinates coordinates_map,bool first_triangle, Posicionable* object, float distance_player_plane){
	if(first_triangle){
		Intersected_object intersected_object(distance_player_plane,object,coordinates_map.y,X_SIDE);
		return intersected_object;
	}else{
		Intersected_object intersected_object(distance_player_plane,object,coordinates_map.x,Y_SIDE);
		return intersected_object;
	}
}

Coordinates Ray::get_coordinates_to_next_block(const Coordinates &ray_position, bool &first_triangle){

	double x_distance = get_x_distance_to_side(ray_position);
	double y_height = x_distance * (ray_direction.y/ray_direction.x);

	double y_distance  = get_y_distance_to_side(ray_position);
	double x_height = y_distance * tan(M_PI/2 - atan((ray_direction.y/ray_direction.x)));

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
	return coordinates_map;
}

Intersected_object Ray::wall_colided(Coordinates coordinates_map,bool first_triangle,Posicionable *object){
	double distance_player_plane = get_distance_to_player_plane(coordinates_map,first_triangle);
	distances.push_back(distance_player_plane);	
	return get_wall(coordinates_map, first_triangle, object, distance_player_plane);
}

Intersected_object Ray::sprite_colided(Coordinates coordinates_map){
	return search_object(coordinates_map);
}

Intersected_object Ray::search_object(Coordinates ray_position){
	bool first_triangle = false; //qué triangulo use despues me afecta en calcular la distancia y el ángulo
	Coordinates coordinates_map = get_coordinates_to_next_block(ray_position, first_triangle);
	Coordinates coordinates_elements = coordinates_map;
	Posicionable* object;
	
	if((object = get_element(coordinates_elements))!=nullptr){
		return object->colisioned(this,coordinates_map, first_triangle);
	}
	return search_object(coordinates_map);	
}

Intersected_object Ray::get_colisioned_objects(){
	return search_object(player_position);
}
