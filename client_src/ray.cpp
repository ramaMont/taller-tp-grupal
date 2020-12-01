#include "ray.h"

static const int X_SIDE = 1;
static const int Y_SIDE = 2;

Ray::Ray(const double &ray_angle,const Coordinates &ray_direction,\
	const Coordinates &player_position,const Coordinates &player_direction,\
	Mapa &map):
	player_direction(player_direction),
	player_position(player_position), 
	ray_direction(ray_direction), 
	direction_relative_to_player(ray_angle) ,
	map(map) {}

//Eventualmente en lugar de devolver bool, va a devolver el puntero
Posicionable* Ray::get_element(const Coordinates &map_coordinates){
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

	whole_coordinates.x = (int)whole_coordinates.x;
	whole_coordinates.y = (int)whole_coordinates.y;

	return (map.obtenerPosicionableEn(whole_coordinates));
}

double Ray::get_distance_to_player_plane(const Coordinates &object_coordinates,const bool &first_triangle){
	double distance;
	double hip = object_coordinates.calculate_distance(player_position);
	if(first_triangle){
		distance = cos(direction_relative_to_player)*hip;
	}else{
		distance = sin((PI/2 - direction_relative_to_player))*hip;
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




Intersected_object Ray::search_object(Coordinates ray_position){
	bool first_triangle = false; //qué triangulo use despues me afecta en calcular la distancia y el ángulo

	double x_distance = get_x_distance_to_side(ray_position);
	double y_height = x_distance * (ray_direction.y/ray_direction.x);

	double y_distance  = get_y_distance_to_side(ray_position);
	double x_height = y_distance * tan(PI/2 - atan((ray_direction.y/ray_direction.x)));

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
	Posicionable* object;
	if((object = get_element(coordinates_map))!=nullptr){
		double distance_player_plane = get_distance_to_player_plane(coordinates_map,first_triangle);
		//Intersected_object *intersected_object = new Intersected_object(distance_player_plane);//Despues cambiarlo, q no sea un puntero
		if(first_triangle){
			return Intersected_object(distance_player_plane,coordinates_map.y,X_SIDE);
		}else{
			return Intersected_object(distance_player_plane,coordinates_map.x,Y_SIDE);
		}
		
	}else{
		return search_object(coordinates_map);
	}	
}

Intersected_object Ray::get_colisioned_object(){
	return search_object(player_position);
}
