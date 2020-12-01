#ifndef RAY_H
#define RAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <exception>

#include <math.h>
#include <string>
#include <vector>

#include "Mapa.h"
#include "coordinates.h"
#include "Posicionable.h"
#include "intersected_object.h"

// Implementa un único rayo del raycasting
class Ray {

const double PI= 3.14159265358979323;

	private:
		const Coordinates &player_direction;
		const Coordinates &player_position;
		const Coordinates &ray_direction;
		const double &direction_relative_to_player;
		Mapa &map;



		// Me fijo si una posicion en el mapa tiene algún elemento(es decir, su valor en la matriz NO es 0)
		Posicionable* get_element(const Coordinates &map_coordinates);

		// Calcula la distancia desde el jugador al objeto con el que impactó el rayo
		double get_distance_to_player_plane(const Coordinates &object_coordinates,const bool &first_triangle);

		/* Recursiva,Calculo el triangulo formado por mi posicion y 
		el borde en el eje x, y el de la posicion y el borde en el eje y,
		se queda con el mas chico (es decir, el que choca primero con una pared),
		 y se fija si toca un objeto, caso contrario, se llama a si misma con 
		 ésta nueva posicion*/
		Intersected_object search_object(Coordinates coordinatess);

		// Calcula la distancia desde mi posicion en x, hasta el borde de mi casillero según la direccion de mi rayo
		double get_x_distance_to_side(const Coordinates &ray_position);

		// Calcula la distancia desde mi posicion en y, hasta el borde de mi casillero según la direccion de mi rayo
		double get_y_distance_to_side(const Coordinates &ray_position);


	public:
		//Ray angle y ray_direction NO es lo mismo, la primera es relativa al plano de la camara y la segunda NO
		Ray(const double &ray_angle,const Coordinates &ray_direction,const Coordinates &player_position,const Coordinates &player_direction, Mapa &map);

		/*Llama a la funcion recursiva que encuentra al objeto con 
		el que choca el rayo, partiendo de la posicion inicial, player_position*/
		Intersected_object get_colisioned_object();

};
#endif
