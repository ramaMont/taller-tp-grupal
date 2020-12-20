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


    void show(SDL_Texture* texture,int x_pixel_line,int x_initial_pos,int x_lenght_ray, float pixel_length,int initial_position_y);

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

    // Carga la textura en windows
    void show_y_pixel_line(int num_texture,bool shaded,int x_pixel_line,int x_initial_pos,int x_lenght_ray, float pixel_length,int initial_position_y);

    void show_sprite(int pos_x, float distance_player_plane, int number_line_texture, int texture);

    void show_enemy(int frame, int state,int enemy,int pos_x, float distance_player_plane, int number_line_texture);    

    void show_gun(int frame_gun, int current_gun);

    // Destruye los recursos creados
    ~Texture();
};

#endif
