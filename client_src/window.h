#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window{

private:
    int width;
    int height;
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    Window(int width, int height);
    void set_no_color();
    void set_color(int r, int g, int b, int alpha);
    int get_width() const;
    int get_height() const;
    void render();
    SDL_Renderer* getRenderer() const;
    ~Window();
};    

#endif
