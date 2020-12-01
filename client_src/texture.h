#ifndef TEXTURE_H
#define TEXTURE_H
#include <string>

#include "window.h"


class Texture {

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;


public:
    // Carga una textura
    Texture(const std::string &filename,const Window& window);

    // Destruye los recursos creados
    ~Texture();

    // Carga la textura en windows
    void show_image(int pos_x, int pos_y, int width, int height) const;
};

#endif
