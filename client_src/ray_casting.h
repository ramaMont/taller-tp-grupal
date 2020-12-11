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
class Intersected_object;
#include "intersected_object.h"
class Sprite;
#include <Sprite.h>

#include <Jugador.h>
#include <Mapa.h>
#include <coordinates.h>

#define texWidth 64
#define texHeight 64

//Implementa el raycasting
class Raycasting {

private:
	int wall_textures[8][3][64][64];//Textura; color(r,g,b); fila; columna
	int other_textures[2][3][64][64];//Texturas de barriles/lamparas
	int guard_textures[3][3][64][64];//Guardia de frente, de costado, y de atras

	Jugador &player;
	Mapa &map;
	SDL_Renderer* renderer;
	float height;
	float widht;	
	SDL_Rect pixel;
	Background background;
	int n_rays;
	std::vector<Sprite*> &sprites;

	void load_wall_texture(std::string file_name,int number_texture);

	void load_ohter_texture(std::string file_name,int number_texture);

	void load_guard_texture(std::string file_name,int number_texture);

	void init_textures();

	void init_pixel(SDL_Rect &pixel, const float &pixel_lenght, int pos_x);



public:
    Raycasting(std::vector<Sprite*> &barrels, Jugador &a_player, Mapa &map, const Window &window);

	void draw_sprites(int pos_x, float distance_player_plane, int number_line_texture, int texture);

	void draw_wall(int pos_x,float distance_player_plane, int number_line_texture, int texture, int side_division);

    //Llama a Ray por cada rayo nuevo, y una vez obtenida su longitud la manda a draw
    void calculate_ray_casting();
};

#endif
