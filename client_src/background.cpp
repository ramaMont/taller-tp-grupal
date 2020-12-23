#include "background.h"

Background::Background(const Window &window) : renderer(window.getRenderer()) 
{
	roof.x = 0;
	roof.y = (window.get_height() - 112)/2;
	roof.w = window.get_width();
	roof.h = (window.get_height() - 112)/2;
}

void Background::show(){
    SDL_SetRenderDrawColor(renderer, 62, 62, 62, SDL_ALPHA_OPAQUE );//Color piso
    SDL_RenderFillRect( renderer, &roof );
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); //Color techo
}

Background::~Background(){
}