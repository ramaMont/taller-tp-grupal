#ifndef DRAWER_H
#define DRAWER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <exception>

#include <fstream>
#include <Jugador.h>

#include "window.h"

#define texWidth 64
#define texHeight 64

// Fondo del juego: el piso y el techo
class Drawer {

	private:
		int wall_textures[8][3][64][64];//Textura; color(r,g,b); fila; columna
		int other_textures[3][3][64][64];//Texturas de barriles/lamparas
		int guard_textures[3][3][64][64];//Guardia de frente, de costado, y de atras

		Jugador &player;
		SDL_Renderer* renderer;
		SDL_Rect pixel;
		int widht;
		int height;
		int n_rays;


		void load_wall_texture(std::string file_name,int number_texture){
		  std::ifstream file("textures/"+file_name);
		  std::string number;

		  for(int k=0; k<3; k++){
			  for(int i=0; i<64; i++){
				  for(int j=0; j<64; j++){
				  	getline(file,number);
				  	wall_textures[number_texture][k][i][j] = stoi(number);
				  }  	
			  }
		  }	
		  file.close();
		}

		void load_ohter_texture(std::string file_name,int number_texture){
		  std::ifstream file("textures/"+file_name);
		  std::string number;

		  for(int k=0; k<3; k++){
			  for(int i=0; i<64; i++){
				  for(int j=0; j<64; j++){
				  	getline(file,number);
				  	other_textures[number_texture][k][i][j] = stoi(number);
				  }  	
			  }
		  }	
		  file.close();
		}

		void load_guard_texture(std::string file_name,int number_texture){
		  std::ifstream file("textures/"+file_name);
		  std::string number;

		  for(int k=0; k<3; k++){
			  for(int i=0; i<64; i++){
				  for(int j=0; j<64; j++){
				  	getline(file,number);
				  	guard_textures[number_texture][k][i][j] = stoi(number);
				  }  	
			  }
		  }	
		  file.close();
		}		

		void init_textures(){

			load_wall_texture("greystone.mat",0);
			load_wall_texture("bluestone.mat",1);
			load_wall_texture("purplestone.mat",2);
			load_wall_texture("colorstone.mat",3);
			load_wall_texture("eagle.mat",4);
			load_wall_texture("mossy.mat",5);
			load_wall_texture("redbrick.mat",6);
			load_wall_texture("wood.mat",7);

			load_ohter_texture("barrel.mat",0);
			load_ohter_texture("pillar.mat",1);
			load_ohter_texture("greenlight.mat",2);

			load_guard_texture("front_guard.mat",0);
			load_guard_texture("side_guard.mat",1);
			load_guard_texture("back_guard.mat",2);

		}		

		void init_pixel(SDL_Rect &pixel, const float &pixel_lenght, const int pos_x){
			float x_lenght_ray = widht/(2*n_rays);//No sé como llamar ésto, es simplemente un calculo q hago acá para no hacer muchas veces despues

			pixel.w = x_lenght_ray;
			pixel.h = ceil(pixel_lenght);

			int x_initial_pos;
		    if(player.get_direction().y>0){
		    	x_initial_pos = x_lenght_ray*(pos_x+n_rays);
		    }else{
		    	x_initial_pos = widht - x_lenght_ray*(pos_x+n_rays);
		    }

			pixel.x = x_initial_pos;
		}


	public:
		Drawer(const Window &window,const int n_rays, Jugador &player):
			player(player),renderer(window.getRenderer()),
			widht(window.get_width()), height(window.get_height()),
			n_rays(n_rays){
				init_textures();
			}

		void draw_sprites(int pos_x, float distance_player_plane, int number_line_texture, int texture){
			float lineHeight = (height / distance_player_plane);
			float initial_position_y =  -lineHeight/2 + height/2;

			float pixel_lenght = lineHeight/64;
			init_pixel(pixel,pixel_lenght,pos_x);

			for(int i=0; i<64; i++){
				int red = other_textures[texture][0][number_line_texture][i];
				int green = other_textures[texture][1][number_line_texture][i];
				int blue = other_textures[texture][2][number_line_texture][i];
				if((red==0) and (green==0) and (blue==0)){
				}else{
					SDL_SetRenderDrawColor(renderer,red , green, blue, SDL_ALPHA_OPAQUE);
					SDL_RenderFillRect( renderer, &pixel );
				}
			   	pixel.y = initial_position_y + ceil((i*pixel_lenght));    	
			}

		}


		void draw_guard(int pos_x, float distance_player_plane, int number_line_texture, int texture){
			float lineHeight = (height / distance_player_plane);
			float initial_position_y =  -lineHeight/2 + height/2;

			float pixel_lenght = lineHeight/64;
			init_pixel(pixel,pixel_lenght,pos_x);

			for(int i=0; i<64; i++){
				int red = guard_textures[texture][0][number_line_texture][i];
				int green = guard_textures[texture][1][number_line_texture][i];
				int blue = guard_textures[texture][2][number_line_texture][i];
				if((red==152) and (green==0) and (blue==136)){
				}else{
					SDL_SetRenderDrawColor(renderer,red , green, blue, SDL_ALPHA_OPAQUE);
					SDL_RenderFillRect( renderer, &pixel );
				}
			   	pixel.y = initial_position_y + ceil((i*pixel_lenght));    	
			}

		}		

		void draw_wall(int pos_x,float distance_player_plane, int number_line_texture, int texture, int side_division){


			float lineHeight = (height / distance_player_plane);
			float initial_position_y =  -lineHeight/2 + height/2;

			float pixel_lenght = lineHeight/64;
			init_pixel(pixel, pixel_lenght, pos_x);	
			
			for(int i=0; i<64; i++){
				int red = wall_textures[texture][0][number_line_texture][i]/side_division;
				int green = wall_textures[texture][1][number_line_texture][i]/side_division;
				int blue = wall_textures[texture][2][number_line_texture][i]/side_division;
				SDL_SetRenderDrawColor(renderer,red , green, blue, SDL_ALPHA_OPAQUE);
			   	pixel.y = initial_position_y + ceil((i*pixel_lenght));
			    SDL_RenderFillRect( renderer, &pixel );    	
			}
		}

};
#endif
