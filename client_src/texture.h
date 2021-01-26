#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>

#include "window.h"
#include <vector>

#include <SDL2/SDL_ttf.h>

class Texture {

private:
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> wall_textures;
    std::vector<SDL_Texture*> sprites;
    std::vector<SDL_Texture*> enemies;
    std::vector<SDL_Texture*> shooting_effect;
    SDL_Texture* guns;
    SDL_Texture* door;
    SDL_Texture* life_bar;
    int height;
    int width;
    SDL_Rect imgPartRect;
    int x_lenght_ray; //Prox: ancho pixel: ancho_pantalla/cant_pixeles_x

    TTF_Font* Sans;

    // Carga todas las texturas de paredes
    void add_wall_texture(std::string new_texture);

    // Carga todas las texturas de sprites
    void add_sprite_texture(std::string new_texture);

    // Carga todas las texturas de efectos de disparo
    void add_shooting_effect_texture(std::string new_texture);

    // Carga todas las texturas de enemigos
    void add_enemy_texture(std::string new_texture);

    // Carga todas las texturas de las armas
    void add_gun_texture(std::string new_texture);

    // Carga todas las texturas de las puertas
    void add_door_textures();   

    // Carga todas las texturas de la barra de vidas
    void add_life_bar_texture(std::string new_texture);

    //Grafica los pixeles solicitados de la textura recibida en la posicion recibida
    void generic_show(SDL_Texture* texture, int first_x_pixel, int cant_x_pixels, int first_y_pixel, int cant_y_pixel,\
        int windows_x_pos, int length_x, int windows_y_pos, int lenght_y);

    //configura los parametros y llama al generic_show para graficar toda el arma
    void show_weapon(int frame_gun, int current_gun, int left_start_texture, int right_end_texture);

    void show_text(std::string text, int letter_width, int letter_height, int x_pos);

    //configura los parametros y llama al generic_show para graficar una unica linea de pixeles de la pared
    void show_wall(SDL_Texture* texture,int x_pixel,float distance_player_plane, int number_line_texture);

    //configura los parametros y llama al generic_show para graficar la parte visible del enemigo
    void show_enemy(SDL_Texture* texture, int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture);

public:

    Texture(const Window& window);

    //Muestra la barra de vida
    void show_life_bar(unsigned int score, int lives, int health, int ammo);

    //configura los parametros y llama al generic_show para graficar la parte visible del sprite
    void show_sprite(int first_x_pixel,int first_number_line_texture,int last_x_pixel, int last_number_line_texture,float distance_player_plane,int texture);

    //llama al show enemy con la textura del perro
	void show_dog(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture, bool is_shooting);

    //llama al show enemy con la textura del guardia
	void show_guard(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture, bool is_shooting);

    //llama al show enemy con la textura del oficial
	void show_officer(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture, bool is_shooting);

    //llama al show enemy con la textura del ss
	void show_ss(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture, bool is_shooting);

    //llama al show enemy con la textura del mutante
	void show_mutant(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture, bool is_shooting);

    //llama al show wall con la textura de la pared gris
	void show_wall_greystone(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la pared azul
	void show_wall_bluestone(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la pared purplestone
	void show_wall_purplestone(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la pared de colores
	void show_wall_colorstone(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la pared agila
	void show_wall_eagle(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la pared mohosa
	void show_wall_mossy(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la pared de ladrillo
	void show_wall_redbrick(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la pared de madera
	void show_wall_wood(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

    //llama al show wall con la textura de la puerta azul
    void show_door(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y);

    //llama al show weapon con la textura del cuchillo
	void show_knife(int frame_gun);

    //llama al show weapon con la textura de la pistola
	void show_gun(int frame_gun);

    //llama al show weapon con la textura de la ametralladora
	void show_machine_gun(int frame_gun);

    //llama al show weapon con la textura del cañon de cadena
	void show_chain_gun(int frame_gun);

    // Destruye las texturas iniciadas
    ~Texture();
};

#endif
