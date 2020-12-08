#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <exception>
#include <math.h>
#include <string>
#include <vector>


#include "window.h"
#include "background.h"
#include "sprite.h"
#include "intersected_object.h"

#include <Jugador.h>
#include <Mapa.h>
#include <coordinates.h>
#include <Barrel.h>

#define texWidth 64
#define texHeight 64

//Implementa el raycasting
class Raycasting {

private:
	int wall_textures[8][3][64][64];//Textura; color(r,g,b); fila; columna
	int other_textures[2][3][64][64];//Texturas de barriles/lamparas

	Jugador &player;
	Mapa map;
	SDL_Renderer* renderer;
	Background background;
	float h;
	int n_rays;
	std::vector<Barrel*> &sprites;

	void load_wall_texture(std::string file_name,int number_texture);

	void load_ohter_texture(std::string file_name,int number_texture);

	void init_textures();

	void draw_wall(Intersected_object intersected_object, int pos_x);

	void draw_barrel(Sprite sprite, int pos_x, int num_pixel, int texture);

	//Dibuja un rayo del raycasting
	void draw(int pos_x);



public:
    Raycasting(std::vector<Barrel*> &barrels, Jugador &a_player, Mapa &map, const Window &window);

    //Llama a Ray por cada rayo nuevo, y una vez obtenida su longitud la manda a draw
    void calculate_ray_casting();
};

#endif
