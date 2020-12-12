#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <exception>
#include <vector>

#include <thread>

#include <chrono>
#include <iostream>
#include <sys/time.h>
#include <ctime>

#include "window.h"
#include "Screen.h"

#include <Mapa.h>
#include <coordinates.h>
#include <Jugador.h>
#include <Direccion.h>
#include <Wall.h>
#include <Sprite.h>
#include <Guard.h>

void draw(Jugador &player, Window &window, Screen &screen,SDL_bool &done){

    DirAdelante forward;
    DirAtras backward;
    DirIzquierda left;
    DirDerecha right;
    DirRotDerecha rotRight;
    DirRotIzquierda rotLeft;

    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    SDL_Event event;



        if(keys[SDL_SCANCODE_RIGHT])
          player.mover(&rotRight);
        if(keys[SDL_SCANCODE_LEFT])
          player.mover(&rotLeft);
        if(keys[SDL_SCANCODE_UP])
          player.mover(&forward);
        if(keys[SDL_SCANCODE_DOWN])
          player.mover(&backward);

	      while (SDL_PollEvent(&event)) { 

	        switch(event.type) {
	          case SDL_QUIT: {
	            done = SDL_TRUE;
	          }
	        }
	      }

         window.set_no_color();
         screen.show();
         window.render(); 
      //SDL_Delay(5);
}

void constant_loop(Jugador &player, Window &window, Screen &screen){ //1000/30

	SDL_bool done = SDL_FALSE;

	long int frames_counter = 0;
	long int counter = 0;

	time_t rate = 1000/30;

    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    time_t time_before_draw;// = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
    time_t time_after_draw;

    time_t time_previous_draw;
    time_previous_draw = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);    		

    while(!done){
    	//LLamo al dibujadorrr
	    gettimeofday(&time_now, nullptr);
		time_before_draw = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);    	

    	draw(player,window,screen,done);
	    
	    gettimeofday(&time_now, nullptr);
	    time_after_draw = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);    	
	    frames_counter+=(time_after_draw - time_previous_draw);
	    counter++;
	    time_previous_draw = time_after_draw;
	    time_t rest = rate - (time_after_draw - time_before_draw);
	    /*if (rest < 0){ //Me tardé mas que mi rate en dibujar este frame
            time_t behind = -rest; //Que tan atrasado estoy
            rest = rate - behind % rate; //
            time_t lost = behind + rest;
            time_start += lost;
            //it += int(lost / rate);//  # floor division
	    }*/	
	    std::this_thread::sleep_for(std::chrono::milliseconds(rest));
    }
    printf("promedio : %li \n", frames_counter/counter);

	/*SDL_bool done = SDL_FALSE;

	time_t rate = 1000/30;

    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    time_t time_start = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);

    while(!done){
    	//LLamo al dibujadorrr
    	draw(player,window,screen,done);
	    gettimeofday(&time_now, nullptr);
	    time_t time_after_draw = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);    	
	    std::cout << "time_after_draw: "  << time_after_draw << std::endl << std::endl;
	    time_t rest = rate - (time_after_draw - time_start);
	    if (rest < 0){ //Me tardé mas que mi rate en dibujar este frame
            time_t behind = -rest; //Que tan atrasado estoy
            rest = rate - behind % rate; //
            time_t lost = behind + rest;
            time_start += lost;
            //it += int(lost / rate);//  # floor division
	    }
	    std::this_thread::sleep_for(std::chrono::milliseconds(rest));
	    //sleep(rest);
	    time_start += rate;
    }*/
}

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
    std::vector<Guard*> guards;
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
	            Guard *posicionable = new Guard(position,a_map[i][j]-10,player);//Esta textura ahora mismo representa si esta de costado o de frente, deberia representar qué enemigo es
	            sprites.push_back(posicionable);
	            guards.push_back(posicionable);
	            map.agregarPosicionable(posicionable,position);	          	
	          }
    		}
    	}
    }

    Window window(640,480);  //(640,480) o bien (1280,720)

    Screen screen(sprites,player,map,window);

    window.set_no_color();

    screen.show();
    window.render();  

    DirAdelante forward;
    DirAtras backward;
    DirIzquierda left;
    DirDerecha right;
    DirRotDerecha rotRight;
    DirRotIzquierda rotLeft;

    constant_loop(player,window,screen);

    return 0;

}

