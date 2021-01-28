#include "ray.h"

#include "Wall.h"
#include "Door.h"

static const int X_SIDE = 1;
static const int Y_SIDE = 2;

Ray::Ray(const double &ray_angle,const Coordinates &ray_direction,\
	std::vector<float> &distances,const Coordinates &player_position,const Coordinates &player_direction,\
	Cl_Mapa &map, int num_ray, int _n_rays):
	player_direction(player_direction),
	player_position(player_position), 
	ray_direction(ray_direction), 
	direction_relative_to_player(ray_angle) ,
	distances(distances),
	map(map),
	num_ray(num_ray),
	n_rays(_n_rays) {}

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

void Ray::wall_colided(Coordinates coordinates_map,bool first_triangle,Wall *object){
	double distance_player_plane = get_distance_to_player_plane(coordinates_map,first_triangle);
	distances.push_back(distance_player_plane);	

	float coordinates_colided_side = 0;
	if(first_triangle)
		coordinates_colided_side = coordinates_map.y;
	else
		coordinates_colided_side = coordinates_map.x;

	float position = floor ((coordinates_colided_side - floor(coordinates_colided_side))*64);

	object->draw(num_ray + n_rays, distance_player_plane,position, first_triangle );

}

void Ray::x_door_colided(Coordinates coordinates_map,bool first_triangle,Door *object){
	bool second_triangle = false;
	Coordinates next_coordinates = get_coordinates_to_next_block(coordinates_map, second_triangle);
	Coordinates coordinates_elements = next_coordinates;

	double door_position = 0;
	bool door_edges_colided = false;
	if(ray_direction.y>0){
		door_position = coordinates_map.y + 0.5;
		door_edges_colided = next_coordinates.y<door_position;
	}else{
		door_position = coordinates_map.y - 0.5;
		door_edges_colided = next_coordinates.y>door_position;
	}

	if(door_edges_colided){//Choco contra los bordes de la puerta antes de la puerta misma
		Posicionable* object = get_element(coordinates_elements);
		object->colisioned(this,next_coordinates, second_triangle);
	}else{
		double n = std::abs(0.5/ray_direction.y);
		coordinates_map.x+= ray_direction.x*n;
		coordinates_map.y+= ray_direction.y*n;

		float coordinates_colided_side = coordinates_map.x;
		
		/*if(first_triangle)
			coordinates_colided_side = coordinates_map.y;
		else
			coordinates_colided_side = coordinates_map.x;*/


		float position = floor ((coordinates_colided_side - floor(coordinates_colided_side))*64);
		float limit_wall = object->get_limit_wall();
		/* Sino... le pido la cantidad de pixeles que YA no puede mostrar, empieza con 0 y despues termina con 64.
		Y a poisiton le resto ese numero, si el resultado es negativo, ya no puedo dibujar nada ahi y 
		sigo dibujando lo que siga... creo
		*/
		if(position<limit_wall){
			double distance_player_plane = get_distance_to_player_plane(coordinates_map,first_triangle);
			distances.push_back(distance_player_plane);
			//object->draw(num_ray + n_rays, distance_player_plane,position, first_triangle );
			object->draw(num_ray + n_rays, distance_player_plane,limit_wall - position, first_triangle );
		}else{
			search_object(coordinates_map);
		}
	}
}

void Ray::y_door_colided(Coordinates coordinates_map,bool first_triangle,Door *object){
	bool second_triangle = false;
	Coordinates next_coordinates = get_coordinates_to_next_block(coordinates_map, second_triangle);
	Coordinates coordinates_elements = next_coordinates;

	double door_position = 0;
	bool door_edges_colided = false;
	if(ray_direction.x>0){
		door_position = coordinates_map.x + 0.5;
		door_edges_colided = next_coordinates.x<door_position;
	}else{
		door_position = coordinates_map.x - 0.5;
		door_edges_colided = next_coordinates.x>door_position;
	}

	if(door_edges_colided){//Choco contra los bordes de la puerta antes de la puerta misma
		Posicionable* object = get_element(coordinates_elements);
		object->colisioned(this,next_coordinates, second_triangle);
	}else{
		double n = std::abs(0.5/ray_direction.x);
		coordinates_map.x+= ray_direction.x*n;
		coordinates_map.y+= ray_direction.y*n;


		float coordinates_colided_side = coordinates_map.y;
		
		/*if(first_triangle)
			coordinates_colided_side = coordinates_map.y;
		else
			coordinates_colided_side = coordinates_map.x;*/

		float position = floor ((coordinates_colided_side - floor(coordinates_colided_side))*64);
		float limit_wall = object->get_limit_wall();
		/* Sino... le pido la cantidad de pixeles que YA no puede mostrar, empieza con 0 y despues termina con 64.
		Y a poisiton le resto ese numero, si el resultado es negativo, ya no puedo dibujar nada ahi y 
		sigo dibujando lo que siga... creo
		*/
		if(position<limit_wall){
			double distance_player_plane = get_distance_to_player_plane(coordinates_map,first_triangle);
			distances.push_back(distance_player_plane);
			//object->draw(num_ray + n_rays, distance_player_plane,position, first_triangle );
			object->draw(num_ray + n_rays, distance_player_plane,limit_wall - position, first_triangle );
		}else{
			search_object(coordinates_map);
		}

	}
}

void Ray::door_colided(Coordinates coordinates_map,bool first_triangle,Door *object){
	if(first_triangle)
		y_door_colided(coordinates_map,first_triangle,object);
	else
		x_door_colided(coordinates_map,first_triangle,object);
}

void Ray::sprite_colided(Coordinates coordinates_map){
	search_object(coordinates_map);
}

void Ray::search_object(Coordinates ray_position){
	bool first_triangle = false; //qué triangulo use despues me afecta en calcular la distancia y el ángulo
	Coordinates coordinates_map = get_coordinates_to_next_block(ray_position, first_triangle);
	Coordinates coordinates_elements = coordinates_map;
	Posicionable* object;
	
	if((object = get_element(coordinates_elements))!=nullptr){
		object->colisioned(this,coordinates_map, first_triangle);
	}else{
		search_object(coordinates_map);	
	}
}

void Ray::draw_ray(){
	search_object(player_position);
}
