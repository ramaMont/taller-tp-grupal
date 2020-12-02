#include "proxy.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <exception>
#include <vector>

#include <Direccion.h>

#include <window.h>
#include <texture.h>
#include <Mapa.h>
#include <ray_casting.h>
#include <Jugador.h>
#include <Posicionable.h>

int corre(){
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

    Coordinates initial_position(2.5,2.5);
    Coordinates initial_direction(0,1);
    Jugador player(initial_position,initial_direction,map);

    for(int i=0; i<24; i++){
    	for(int j=0; j<24; j++){
    		if(a_map[i][j]!=0){
		      Coordinates position((float)i,(float)j);
		      Posicionable *posicionable = new Posicionable(position);
		      map.agregarPosicionable(posicionable,position);
    		}
    	}
    }

    Window window(640,480);

    Raycasting ray_casting(player,map,window);

    window.set_no_color();

    ray_casting.calculate_ray_casting();

    window.render();  

    DirAdelante forward;
    DirAtras backward;
    DirIzquierda left;
    DirDerecha right;
    DirRotDerecha rotRight;
    DirRotIzquierda rotLeft;

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
                player.mover(&rotLeft);
                window.set_no_color();
                ray_casting.calculate_ray_casting();  
                window.render();
                break;
              case SDLK_e:
                player.mover(&rotRight);
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
