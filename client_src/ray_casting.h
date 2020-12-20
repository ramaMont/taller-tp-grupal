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
#include <Mapa.h>
#include <coordinates.h>

//Implementa el raycasting
class Raycasting {

private:

	Jugador &player;
	Mapa &map;
	int n_rays;
	Texture &texture_drawer;



public:
    Raycasting(Jugador &a_player, Mapa &map, int n_rays, Texture &texture_drawer);


    //Llama a Ray por cada rayo nuevo, y una vez obtenida su longitud la manda a draw
    void calculate_raycasting(Camera &camera,std::vector<float> &distances);
};

#endif
