#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <exception>

#include "window.h"

#include <math.h>
#include <string>
#include <vector>

#include "Mapa.h"
#include "camera.h"
#include "Jugador.h"
#include "coordinates.h"

#include "ray.h"

//Implementa el raycasting
class Raycasting {

private:
	Jugador &player;
	Mapa map;
	SDL_Renderer* renderer;
	float h;
	int n_rays;

	//Dibuja un rayo del raycasting
	void draw(float distance_player_plane,float pos_x);



public:
    Raycasting(Jugador &a_player, Mapa &map, const Window &window);

    //Llama a Ray por cada rayo nuevo, y una vez obtenida su longitud la manda a draw
    void calculate_ray_casting();
};

#endif
