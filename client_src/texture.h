#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>

#include "window.h"
#include <vector>

class Texture {

private:
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> wall_textures;
    std::vector<SDL_Texture*> sprites;
    std::vector<SDL_Texture*> enemies;
    SDL_Texture* guns;
    int height;
    int width;
    int n_rays;
    SDL_Rect imgPartRect;

    void show_weapon(int frame_gun, int current_gun);

    void show(SDL_Texture* texture,int x_pixel_line,int y_pixel_line,int pos_x, float distance_player_plane);

    void show_sprites(SDL_Texture* texture,int x_pixel_line,int y_pixel_line,int upper_limit, int pos_x, float distance_player_plane);

public:

    // Carga una textura
    Texture(SDL_Renderer* renderer, int height);

    Texture(const Window& window, int n_rays);

    void add_wall_texture(std::string new_texture);

    void add_sprite_texture(std::string new_texture);

    void add_enemy_texture(std::string new_texture);

    void add_gun_texture(std::string new_texture);

    // Carga la textura en windows
    void show_wall(int pos_x,float distance_player_plane, int number_line_texture, int texture, bool wall_side_y);

    void show_sprite(int pos_x, float distance_player_plane, int number_line_texture, int texture);


	void show_dog(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture);

	void show_guard(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture);

	void show_officer(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture);

	void show_ss(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture);

	void show_mutant(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture);



	void show_knife(int frame_gun);

	void show_gun(int frame_gun);

	void show_machine_gun(int frame_gun);

	void show_chain_gun(int frame_gun);

    // Destruye los recursos creados
    ~Texture();
};

#endif
