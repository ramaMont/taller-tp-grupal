#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window{

private:
    int width;
    int height;
    int resolution_width;
    int resolution_high;
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    Window(int width, int height, int resolution_width, int resolution_high);
    void set_no_color();
    void set_color(int r, int g, int b, int alpha);
    int get_width() const;
    int get_height() const;
    int get_resolution_width() const{
        return resolution_width;
    }
    void showWindow();
    void render();
    SDL_Renderer* getRenderer() const;
    ~Window();
};    

#endif
