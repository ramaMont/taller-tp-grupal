#include "background.h"

Background::Background(const Window &window) : renderer(window.getRenderer()) 
{
	roof.x = 0;
	roof.y = 240;
	roof.w = 640;
	roof.h = 240;   
}

void Background::show(){
    SDL_SetRenderDrawColor(renderer, 62, 62, 62, SDL_ALPHA_OPAQUE );//Color piso
    SDL_RenderFillRect( renderer, &roof );
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); //Color techo
}
