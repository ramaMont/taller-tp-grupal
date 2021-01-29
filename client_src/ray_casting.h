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
class Texture;
#include "texture.h"

#include <Player.h>
#include <ClMap.h>
#include <coordinates.h>

//Implementa el raycasting
class Raycasting {

private:

	Player &player;
	ClMap &map;
	int n_rays;



public:
    Raycasting(Player &a_player, ClMap &map, int n_rays);


    //Llama a Ray por cada rayo nuevo, y una vez obtenido, lo dibuja
    void calculate_raycasting(Camera &camera,std::vector<float> &distances);
};

#endif
