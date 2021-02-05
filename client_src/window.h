#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int INFO_BAR_HEIGHT = 112;

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
    void setNoColor();
    void setColor(int r, int g, int b, int alpha);
    int getWidth() const;
    int getHeight() const;
    int getResolutionWidth() const{
        return resolution_width;
    }
    void showWindow();
    void hideWindow();
    void render();
    SDL_Renderer* getRenderer() const;
    ~Window();
};    

#endif
