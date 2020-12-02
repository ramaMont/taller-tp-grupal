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

#include "background.h"
#include "Mapa.h"
#include "camera.h"
#include "Jugador.h"
#include "coordinates.h"

#include "ray.h"
#include "intersected_object.h"

#define texWidth 64
#define texHeight 64

//Implementa el raycasting
class Raycasting {

private:
	int textures[10][3][64][64];//Textura; color(r,g,b); fila; columna

	Jugador &player;
	Mapa map;
	SDL_Renderer* renderer;
	Background background;
	float h;
	int n_rays;

	void load_texture(std::string file_name,int number_texture);

	void init_textures();

	//Dibuja un rayo del ra#include "intersected_object.h"ycasting
	void draw(Intersected_object intersected_object,float pos_x);



public:
    Raycasting(Jugador &a_player, Mapa &map, const Window &window);

    //Llama a Ray por cada rayo nuevo, y una vez obtenida su longitud la manda a draw
    void calculate_ray_casting();
};

#endif
