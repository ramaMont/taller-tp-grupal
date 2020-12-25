#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <exception>
#include <math.h>
#include <string>
#include <vector>

#include "camera.h"
#include "window.h"
#include "background.h"
class Intersected_object;
#include "intersected_object.h"
class Texture;
#include "texture.h"

#include <Jugador.h>
#include <Cl_Mapa.h>
#include <coordinates.h>

//Implementa el raycasting
class Raycasting {

private:

	Jugador &player;
	Cl_Mapa &map;
	int n_rays;



public:
    Raycasting(Jugador &a_player, Cl_Mapa &map, int n_rays);


    //Llama a Ray por cada rayo nuevo, y una vez obtenido, lo dibuja
    void calculate_raycasting(Camera &camera,std::vector<float> &distances);
};

#endif
