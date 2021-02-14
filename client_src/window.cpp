#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_mixer.h>

#include <iostream>

#include "exception.h"
#include "window.h"

#include <ConfigVariable.h>

static const int INITIAL_WIDTH_SIZE = 640;
static const int INITIAL_HEIGHT_SIZE = 400;

//anchoPantalla
Window::Window() :
        width(640), height(400), //Resolucion()
        info_bar_height(height/5) {
    int state = SDL_CreateWindowAndRenderer(
        INITIAL_WIDTH_SIZE, INITIAL_HEIGHT_SIZE, 
        			SDL_RENDERER_ACCELERATED  | 
        			SDL_WINDOW_RESIZABLE | 
        			SDL_WINDOW_HIDDEN,
        &this->window, &this->renderer);
    if (state) {
        throw Exception("Error al crear ventana\n");
    }
    resizeWindow(INITIAL_WIDTH_SIZE,INITIAL_HEIGHT_SIZE);
    // Inicializacion de audio
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        throw Exception("Error al inicializar audio\n");
    }

    // Cantidad de sonidos sonando a la vez: por ahora 32
    Mix_AllocateChannels(32);
}

void Window::showWindow(){
    SDL_ShowWindow(this->window);
}

void Window::disableResizable(){
    SDL_SetWindowResizable(this->window,SDL_FALSE);
}

void Window::resizeWindow(int new_width_size, int new_height_size){
    SDL_RenderSetScale(this->renderer,new_width_size/(float)width,
    									new_height_size/(float)height);
}

void Window::hideWindow(){
    SDL_HideWindow(this->window);
}

void Window::setColor(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer,
                           r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

void Window::setNoColor() {
    this->setColor(0x33,0x33,0x33,0xFF);
}

int Window::getInfoBarHeight() const{
    return info_bar_height;
}

int Window::getWidth()const {
    return width;
}

int Window::getHeight() const{
    return height;
}

void Window::render() {
    SDL_RenderPresent(this->renderer);
}


SDL_Renderer* Window::getRenderer() const {
    return this->renderer;
}

Window::~Window() {
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = nullptr;
    }

    if (this->window) {
        SDL_DestroyWindow(this->window);
        this->window = nullptr;
    }

    SDL_Quit();
}
