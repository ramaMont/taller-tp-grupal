#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <exception>

#include "window.h"


// Fondo del juego: el piso y el techo
class Status_bar {

	private:
		SDL_Renderer* renderer;
		SDL_Rect status_bar;

	public:
		Status_bar(const Window &window) : renderer(window.getRenderer()) {
			status_bar.x = 0;
			status_bar.y = (window.get_height() - 112);
			status_bar.w = window.get_width();
			status_bar.h = 112;
		}

		// Muestra el fondo
		void show(){
		    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE );//Color piso
		    SDL_RenderFillRect( renderer, &status_bar );			
		}

		~Status_bar(){}
};
#endif
