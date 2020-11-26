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

	int width = 500;
	int height = 500;

	Window window(width,height);

	window.set_no_color();

    Texture frames[31] = {Texture("wolfenstein0.jpg", window) , Texture("wolfenstein1.jpg", window),
                         Texture("wolfenstein2.jpg", window) , Texture("wolfenstein3.jpg", window),
                         Texture("wolfenstein4.jpg", window) , Texture("wolfenstein5.jpg", window),
                         Texture("wolfenstein6.jpg", window) , Texture("wolfenstein7.jpg", window),
                         Texture("wolfenstein8.jpg", window) , Texture("wolfenstein9.jpg", window),
                         Texture("wolfenstein10.jpg", window) , Texture("wolfenstein11.jpg", window),
                         Texture("wolfenstein12.jpg", window) , Texture("wolfenstein13.jpg", window),
                         Texture("wolfenstein14.jpg", window) , Texture("wolfenstein15.jpg", window),
                         Texture("wolfenstein16.jpg", window) , Texture("wolfenstein17.jpg", window),
                         Texture("wolfenstein18.jpg", window) , Texture("wolfenstein19.jpg", window),
                         Texture("wolfenstein20.jpg", window) , Texture("wolfenstein21.jpg", window),
                         Texture("wolfenstein22.jpg", window) , Texture("wolfenstein23.jpg", window),
                         Texture("wolfenstein24.jpg", window) , Texture("wolfenstein25.jpg", window),
                         Texture("wolfenstein26.jpg", window) , Texture("wolfenstein27.jpg", window),
                         Texture("wolfenstein28.jpg", window) , Texture("wolfenstein29.jpg", window),
                         Texture("wolfenstein30.jpg", window)};

    int i=0;
    while(i<100){
        frames[i%31].show_image(0,0,width,height);
        window.render();
        SDL_Delay(66);
        i++;
    }

    
    SDL_Quit();
    return 0;
}

