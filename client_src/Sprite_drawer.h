#ifndef __SPRITE_DRAWER__
#define __SPRITE_DRAWER__

#include <iostream>
#include <vector>

#include <math.h>

class Raycasting;
#include "ray_casting.h"

class Posicionable;
#include <Cl_Posicionable.h>

#include <coordinates.h>

// Obtiene la informacion necesaria para dibujar sprites, tanto sprites comunes como enemigos
class Sprite_drawer{
protected:
	Cl_Posicionable* posicionable;
	Jugador &player;
	bool located;
	float player_distance;
	double relative_angle_to_player;
	double lowest_ray_distance;
	int center_ray;
	int cant_rays;


public:
    explicit Sprite_drawer(Cl_Posicionable *posicionable, Jugador &player);

    virtual void draw(const std::vector<float> &distances, int n_rays)  = 0;

    // Calcula su angulo relativo respecto a la direccion del jugador
    void set_relative_angle_to_player();

    // Obtiene el rayo de raycasting mas cercano a su posicion
	void update_distance_to_closest_ray(int i,int n_rays);

	// Calcula la distancia al plano del jugador
	void set_distance(int half_pixels,Coordinates camera_plane);

	// En caso de haber colisionado con un rayo, seteo el sprite como 'avistado'
	void spotted_sprite();

	// True si el sprite fue visto, false en caso contrario
	bool is_spotted();

	// Desactiva el 'avistado' del frame anterior
	void disable_spotted();

	float get_distance_player_plane() const;

};

#endif
