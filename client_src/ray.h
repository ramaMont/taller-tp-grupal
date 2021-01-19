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
//#include "sprite.h"

class Cl_Mapa;
#include <Cl_Mapa.h>
class Posicionable;
#include <Posicionable.h>

class Intersected_object;
#include "intersected_object.h"

class Wall;
class Door;

// Implementa un único rayo del raycasting
class Ray {


	private:
		const Coordinates &player_direction;
		const Coordinates &player_position;
		const Coordinates &ray_direction;
		const double &direction_relative_to_player;

		std::vector<float> &distances;

		Cl_Mapa &map;
		int num_ray;
		int n_rays;

		// Incrementa las coordenas a ver en el mapa según cual de las dos posiciones es entera
		void increment_coordinates(Coordinates &coordinates, int inc_x, int inc_y);

		// Me fijo si una posicion en el mapa tiene algún elemento(es decir, su valor en la matriz NO es 0)
		Posicionable* get_element(Coordinates &map_coordinates);

		// Calcula la distancia desde el jugador al objeto con el que impactó el rayo
		double get_distance_to_player_plane(const Coordinates &object_coordinates,const bool &first_triangle);

		/* Recursiva,Calculo el triangulo formado por mi posicion y 
		el borde en el eje x, y el de la posicion y el borde en el eje y,
		se queda con el mas chico (es decir, el que choca primero con una pared),
		 y se fija si toca un objeto, caso contrario, se llama a si misma con 
		 ésta nueva posicion*/
		void search_object(Coordinates coordinatess);

		// Calcula la distancia desde mi posicion en x, hasta el borde de mi casillero según la direccion de mi rayo
		double get_x_distance_to_side(const Coordinates &ray_position);

		// Calcula la distancia desde mi posicion en y, hasta el borde de mi casillero según la direccion de mi rayo
		double get_y_distance_to_side(const Coordinates &ray_position);

		// Devuelve las coordenadas hacia el proximo bloque con el que choca el rayo
		Coordinates get_coordinates_to_next_block(const Coordinates &ray_position, bool &first_triangle);

		void y_door_colided(Coordinates coordinates_map,bool first_triangle,Door *object);

		void x_door_colided(Coordinates coordinates_map,bool first_triangle,Door *object);


	public:
		//Ray angle y ray_direction NO es lo mismo, la primera es relativa al plano de la camara y la segunda NO
		Ray(const double &ray_angle,const Coordinates &ray_direction,std::vector<float> &distances,const Coordinates &player_position,const Coordinates &player_direction, Cl_Mapa &map, int num_ray, int _n_rays);

		/*Llama a la funcion recursiva que encuentra al objeto con 
		el que choca el rayo, partiendo de la posicion inicial, player_position*/
		void draw_ray();

		//Los objetos contra los que colisioné, que no son paredes,
		// devuelven esta funcion, que llama a la recursiva y continúa buscando una pared
		void sprite_colided(Coordinates coordinates_map);

		// El objeto contra el que colisioné llama a este método si es una pared, y finalizo este rayo		
		void wall_colided(Coordinates coordinates_map,bool first_triangle,Wall *object);

		void door_colided(Coordinates coordinates_map,bool first_triangle,Door *object);


};
#endif
