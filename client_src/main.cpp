#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <exception>
#include <vector>

#include "window.h"
#include "ray_casting.h"

#include <Mapa.h>
#include <coordinates.h>
#include <Jugador.h>
#include <Direccion.h>
#include <Wall.h>
#include <Sprite.h>
#include <Guard.h>
//#include "sprite.h"

int main(int argc, char* argv[]) {

    std::vector<std::vector<int>> a_map{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,8,10,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,9,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,9,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
    
    Mapa map(24, 24);

    Coordinates initial_position(12.5,2.5);
    Coordinates initial_direction(0,1);
    Jugador player(initial_position,initial_direction,map);
    std::vector<Sprite*> sprites;
    for(int i=0; i<24; i++){
    	for(int j=0; j<24; j++){
        int pos_value = a_map[i][j];
    		if(pos_value!=0){
	          if(pos_value<8){
	            Coordinates position((float)i,(float)j);
	  		      Posicionable *posicionable = new Wall(position,a_map[i][j]-1);
	  		      map.agregarPosicionable(posicionable,position);
	          }else if(pos_value<10){
	            Coordinates position((float)i+0.5,(float)j+0.5);
	            Sprite *posicionable = new Sprite(position,a_map[i][j]-8,player);
	            sprites.push_back(posicionable);
	            map.agregarPosicionable(posicionable,position);
	          }else{
	          	Coordinates position((float)i+0.5,(float)j+0.5);
	            Sprite *posicionable = new Guard(position,a_map[i][j]-10,player);//Esta textura ahora mismo representa si esta de costado o de frente, deberia representar qué enemigo es
	            sprites.push_back(posicionable);
	            map.agregarPosicionable(posicionable,position);	          	
	          }
    		}
    	}
    }

    Window window(640,480);  //o bien 1280,720

    Raycasting ray_casting(sprites,player,map,window);

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

    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    while (!done) {
      SDL_Event event;

        if(keys[SDL_SCANCODE_RIGHT])
          player.mover(&rotRight);
        if(keys[SDL_SCANCODE_LEFT])
          player.mover(&rotLeft);
        if(keys[SDL_SCANCODE_UP])
          player.mover(&forward);
        if(keys[SDL_SCANCODE_DOWN])
          player.mover(&backward);
        
         window.set_no_color();
         ray_casting.calculate_ray_casting();
         window.render(); 
      SDL_Delay(20);
      while (SDL_PollEvent(&event)) { 

        switch(event.type) {
          case SDL_QUIT: {
            done = SDL_TRUE;
          }
        }
      }
    }

    return 0;

}

