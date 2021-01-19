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
    SDL_Texture* guns;
    SDL_Texture* door;
    SDL_Texture* life_bar;
    int height;
    int width;
    SDL_Rect imgPartRect;
    int x_lenght_ray; //Prox: ancho pixel: ancho_pantalla/cant_pixeles_x

    TTF_Font* Sans;

    void show_weapon(int frame_gun, int current_gun, int left_start_texture, int right_end_texture);

    void show(SDL_Texture* texture,int x_pixel_line,int y_pixel_line,int pos_x, float distance_player_plane);

    void show_sprites(SDL_Texture* texture,int x_pixel_line,int y_pixel_line,int upper_limit, int pos_x, float distance_player_plane);

    void show_text(std::string text, int letter_width, int letter_height, int x_pos);

public:

    void show_life_bar(unsigned int score, int lives, int health, int ammo);

    Texture(const Window& window);

    // Carga todas las texturas de paredes
    void add_wall_texture(std::string new_texture);

    // Carga todas las texturas de sprites
    void add_sprite_texture(std::string new_texture);

    // Carga todas las texturas de enemigos
    void add_enemy_texture(std::string new_texture);

    // Carga todas las texturas de las armas
    void add_gun_texture(std::string new_texture);

    // Carga todas las texturas de las puertas
    void add_door_textures();   

    void add_life_bar_texture(std::string new_texture);

    void show_sprite(int pos_x, float distance_player_plane, int number_line_texture, int texture);

	void show_dog(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture);

	void show_guard(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture);

	void show_officer(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture);

	void show_ss(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture);

	void show_mutant(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture);

	void show_wall_greystone(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

	void show_wall_bluestone(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

	void show_wall_purplestone(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

	void show_wall_colorstone(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

	void show_wall_eagle(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

	void show_wall_mossy(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

	void show_wall_redbrick(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

	void show_wall_wood(int pos_x,float distance_player_plane, int number_line_texture, bool wall_side_y);

    void show_door(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y);

	void show_knife(int frame_gun);

	void show_gun(int frame_gun);

	void show_machine_gun(int frame_gun);

	void show_chain_gun(int frame_gun);

    // Destruye las texturas iniciadas
    ~Texture();
};

#endif
