#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_mixer.h>
#include "exception.h"
#include "window.h"
#include <iostream>


Window::Window(int width, int height, int resolution_width, int resolution_high) :
        width(width), height(height),resolution_width(resolution_width),resolution_high(resolution_high) {
    int state = SDL_CreateWindowAndRenderer(
        width, height, SDL_RENDERER_ACCELERATED | SDL_WINDOW_HIDDEN,
        &this->window, &this->renderer);
    if (state) {
        throw Exception("Error al crear ventana\n");
    }
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
