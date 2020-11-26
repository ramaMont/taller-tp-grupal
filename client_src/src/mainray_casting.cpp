#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <exception>



#include "window.h"
#include "texture.h"

#include "ray_casting.h"
#include "player.h"

int main(int argc, char* argv[]) {

    std::vector<std::vector<int>> a_map{  {1,1,1,1,1,1,1,1,1,1},
                                          {1,0,0,0,0,0,0,0,0,1},
                                          {1,0,0,0,0,0,0,0,0,1},
                                          {1,1,0,0,1,0,0,0,0,1},
                                          {1,0,0,0,1,1,1,0,0,1},
                                          {1,0,0,0,1,0,1,0,0,1},
                                          {1,0,0,0,1,0,1,0,0,1},
                                          {1,0,0,0,1,0,1,0,0,1},
                                          {1,0,0,0,1,1,1,0,0,1},
                                          {1,1,1,1,1,1,1,1,1,1}};



    Window window(640,480);
    Player player(3.5,3,0,-1);
    Raycasting ray_casting(player,a_map,window);

    window.set_no_color();

    ray_casting.calculate_ray_casting();

    window.render();  

    SDL_bool done = SDL_FALSE;
    while (!done) {
      SDL_Event event;
      while (SDL_PollEvent(&event)) {
        switch(event.type) {
          case SDL_KEYDOWN: {
            SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
            switch (keyEvent.keysym.sym) {
              case SDLK_LEFT:
              player.move_left();
              window.set_no_color();
              ray_casting.calculate_ray_casting();
              window.render();  
                break;
              case SDLK_RIGHT:
                player.move_right();
                window.set_no_color();
                ray_casting.calculate_ray_casting();
                window.render();  
                break;
              case SDLK_UP:
                player.move_forward();
                window.set_no_color();
                ray_casting.calculate_ray_casting();
                window.render();  
                break;
              case SDLK_DOWN:
                player.move_backward();
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

