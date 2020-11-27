#ifndef RAY_H
#define RAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <exception>

#include <math.h>
#include <string>
#include <vector>

#include "coordinates.h"


// Implementa un único rayo del raycasting
class Ray {

const float PI= 3.14159265358979323;

	private:
		const Coordinates &player_direction;
		const Coordinates &player_position;
		const Coordinates &ray_direction;
		const float &direction_relative_to_player;
		const std::vector<std::vector<int>> &map;

		bool es_entero(const float &number);

		// Según la direccion a la que apunta mi rayo, me fijo en una celda distinta
		int get_increase(const float &direction);


		// Me fijo si una posicion en el mapa tiene algún elemento(es decir, su valor en la matriz NO es 0)
		bool has_element(const Coordinates &map_coordinates);

		// Calcula la distancia desde el jugador al objeto con el que impactó el rayo
		float get_distance_to_player_plane(const Coordinates &object_coordinates,const bool &first_triangle);

		/* Recursiva,Calculo el triangulo formado por mi posicion y 
		el borde en el eje x, y el de la posicion y el borde en el eje y,
		se queda con el mas chico (es decir, el que choca primero con una pared),
		 y se fija si toca un objeto, caso contrario, se llama a si misma con 
		 ésta nueva posicion*/
		float search_ray_distance(const Coordinates &coordinatess);


	public:
		//Ray angle y ray_direction NO es lo mismo, la primera es relativa al plano de la camara y la segunda NO
		Ray(const float &ray_angle,const Coordinates &ray_direction,const Coordinates &player_position,const Coordinates &player_direction, const std::vector<std::vector<int>> &map);

		/*Llama a la funcion recursiva que encuentra al objeto con 
		el que choca el rayo, partiendo de la posicion inicial, player_position*/
		float calculate_ray_distance();

};
#endif
