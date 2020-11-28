#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <exception>

#include "Direccion.h"

#include "window.h"
#include "texture.h"
#include "Mapa.h"
#include "ray_casting.h"
#include "Jugador.h"
#include "Posicionable.h"

int main(int argc, char* argv[]) {

    std::vector<std::vector<int>> a_map{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
    Mapa map(24, 24);
    for(int i=0; i<24; i++){
    	for(int j=0; j<24; j++){
    		if(a_map[i][j]!=0){
		      Coordinates position(i,j);
		      Posicionable *posicionable = new Posicionable(position);
		      map.agregarPosicionable(posicionable,position);
    		}
    	}
    }

    /*for(int i=0; i<20; i++){
      Coordinates position(i,0);
      Posicionable *posicionable = new Posicionable(position);
      map.agregarPosicionable(posicionable,position);
    }*///Arreglo esto, rodeo mi mapa con estas cosas, y despuees me aseguro q no explote el ray al llamarlos

   	Coordinates initial_position(3.5,3);
	  Coordinates initial_direction(0,-1);

    Window window(640,480);

    Jugador player(initial_position,initial_direction,map);
    Raycasting ray_casting(player,map,window);

    window.set_no_color();

    ray_casting.calculate_ray_casting();

    window.render();  

    DirAdelante forward;
    DirAtras backward;
    DirIzquierda left;
    DirDerecha right;

    SDL_bool done = SDL_FALSE;
    while (!done) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        switch(event.type) {
          case SDL_KEYDOWN: {
            SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
            switch (keyEvent.keysym.sym) {
              case SDLK_LEFT:
              player.mover(&left);
              window.set_no_color();
              ray_casting.calculate_ray_casting();
              window.render();  
                break;
              case SDLK_RIGHT:
                player.mover(&right);
                window.set_no_color();
                ray_casting.calculate_ray_casting();
                window.render();  
                break;
              case SDLK_UP:
                player.mover(&forward);
                window.set_no_color();
                ray_casting.calculate_ray_casting();
                window.render();  
                break;
              case SDLK_DOWN:
                player.mover(&backward);
                window.set_no_color();
                ray_casting.calculate_ray_casting();
                window.render();  
                break;
              case SDLK_q:
                player.rotate_left();
                window.set_no_color();
                ray_casting.calculate_ray_casting();  
                window.render();
                break;
              case SDLK_e:
                player.rotate_right();
                window.set_no_color();
                ray_casting.calculate_ray_casting();  
                window.render();
                break;
            }
          } // Fin KEY_DOWN
          break;            
          case SDL_QUIT: {
            done = SDL_TRUE;
          }
        }
      }
    }
    return 0;

}

