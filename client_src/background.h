#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <exception>

#include "window.h"

// Fondo del juego: el piso y el techo
class Background {
	private:
		SDL_Renderer* renderer;
		SDL_Rect roof;
	public:
		explicit Background(const Window &window) : renderer(window.getRenderer()){
		    roof.x = 00;
			roof.y = 240;
			roof.w = 640;
			roof.h = 240;	
		}
		// Muestra el fondo
		void show(){
		    // para hacer el techo oscuro, y el piso claro con un triangulo 
			// (despues pasar a otra clase)
		    SDL_SetRenderDrawColor(renderer, 0x6E, 0x6E, 0x6E, 0);
		    SDL_RenderFillRect(renderer, &roof);
		    //SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		}
};
#endif
