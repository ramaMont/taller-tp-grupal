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

#include "camera.h"
#include "player.h"
#include "coordinates.h"

#include "ray.h"

//Implementa el raycasting
class Raycasting {

private:
	Player &player;
	const std::vector<std::vector<int>> &map;
	SDL_Renderer* renderer;
	SDL_Rect roof;
	float h;
	int n_rays;

	//Dibuja un rayo del raycasting
	void draw(float distance_player_plane,float pos_x);



public:
    Raycasting(Player &a_player,const std::vector<std::vector<int>> &a_map,const Window &window);

    //Llama a Ray por cada rayo nuevo, y una vez obtenida su longitud la manda a draw
    void calculate_ray_casting();
};

#endif
