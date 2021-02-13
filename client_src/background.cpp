#include "background.h"

Background::Background(const Window &window) : renderer(window.getRenderer()) 
{
	roof.x = 0;
	roof.y = (window.getHeight()-window.getInfoBarHeight())/2;
	roof.w = window.getWidth();
	roof.h = (window.getHeight()-window.getInfoBarHeight())/2;
}

void Background::show(){
    SDL_SetRenderDrawColor(renderer, 62, 62, 62, SDL_ALPHA_OPAQUE);//Piso
    SDL_RenderFillRect(renderer, &roof);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); //Techo
}

Background::~Background(){
}
