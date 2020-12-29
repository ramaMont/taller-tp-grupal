#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_render.h>
#include "exception.h"
#include "window.h"
#include <iostream>


Window::Window(int width, int height, int resolution_width, int resolution_high) :
        width(width), height(height),resolution_width(resolution_width),resolution_high(resolution_high) {
    int state = SDL_CreateWindowAndRenderer(
        width, height, SDL_RENDERER_ACCELERATED | SDL_WINDOW_HIDDEN,
        &this->window, &this->renderer);
    if (state) {
        throw Exception("Error al crear ventana");
    }   
}

void Window::showWindow(){
    SDL_ShowWindow(this->window);
}

void Window::set_color(int r, int g, int b, int alpha) {
    SDL_SetRenderDrawColor(this->renderer,
                           r, g, b, alpha);
    SDL_RenderClear(this->renderer);
}

void Window::set_no_color() {
    this->set_color(0x33,0x33,0x33,0xFF);
}

int Window::get_width()const {
    return width;
}

int Window::get_height() const{
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
