#include "texture.h"
#include <SDL2/SDL_image.h>
#include <string>

#include <SDL2/SDL.h>

Texture::Texture(const std::string &filename,const Window& window)
    : renderer(window.getRenderer()) 
    {
    this->texture = IMG_LoadTexture(renderer, filename.c_str());
}


void Texture::show_image(int pos_x, int pos_y, int width, int height) const{
    const SDL_Rect sdlSrc = {
        pos_x, pos_y,
        width, height
    };    

    SDL_RenderCopy(this->renderer, this->texture, &sdlSrc, &sdlSrc);
}

Texture::~Texture() {
    SDL_DestroyTexture(this->texture);
}