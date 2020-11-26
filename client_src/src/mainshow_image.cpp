#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <exception>


//Todavia no los uso
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "window.h"
#include "texture.h"

int main(int argc, char* argv[]) {

	int width = 1000;
	int height = 500;

	Window window(width,height);

	window.set_no_color();

	Texture image("wolfstein.jpg", window);

    image.show_image(0,0,width,height);

    window.render();

    char stop = 'a';
    while(stop!='q'){
    	stop = getchar();
    }
    
    SDL_Quit();
    return 0;
}

