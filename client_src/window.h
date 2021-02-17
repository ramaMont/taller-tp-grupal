#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Window{
private:
    int width; //Resolucion de ancho 
    int height; //Resolucion de alto
    int info_bar_height;
    bool fullscreen;
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    Window(int resolution_width, int resolution_height, bool fullscreen);

    Window(const Window&) = delete;
    Window(Window&& other) = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&& other);

    void setNoColor();
    void setColor(int r, int g, int b, int alpha);
    int getWidth() const;
    int getHeight() const;

    void disableFullscreen();
    void disableResizable();

    void resizeWindow(int newWidth, int newHeight);

    int getInfoBarHeight() const;
    void showWindow();
    void hideWindow();
    void render();
    SDL_Renderer* getRenderer() const;
    ~Window();
};    

#endif
