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
		explicit Background(const Window &window);
		// Muestra el fondo
		void show();
};
#endif
