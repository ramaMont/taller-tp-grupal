#include <math.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include "ray_casting.h"

#include "window.h"

#include "camera.h"
#include "Jugador.h"
#include "coordinates.h"

#include "ray.h"

void Raycasting::load_texture(std::string file_name,int number_texture){
  std::ifstream file("textures/"+file_name);
  std::string number;

  for(int k=0; k<3; k++){
	  for(int i=0; i<64; i++){
		  for(int j=0; j<64; j++){
		  	getline(file,number);
		  	textures[number_texture][k][i][j] = stoi(number);
		  }  	
	  }
  }	
  file.close();
}

void Raycasting::init_textures(){

	load_texture("greystone.mat",0);
	load_texture("bluestone.mat",1);
	load_texture("purplestone.mat",2);
	load_texture("colorstone.mat",3);
	load_texture("eagle.mat",4);
	load_texture("mossy.mat",5);
	load_texture("redbrick.mat",6);
	load_texture("wood.mat",7);

}


Raycasting::Raycasting(Jugador &a_player,Mapa &a_map,const Window &window)
    : player(a_player), map(a_map),renderer(window.getRenderer()), background(window)
    {
    h = 480;
    n_rays = 160;
    init_textures();
}


void Raycasting::draw(Intersected_object intersected_object,float pos_x){


	float distance_player_plane = intersected_object.get_distance_player_plane();
	float lineHeight = (h / distance_player_plane);
	int number_line_texture = intersected_object.get_number_line_texture();
	int side_division = intersected_object.get_side_division();
	float initial_position_y =  -lineHeight/2 + h/2;

	SDL_Rect pixel;

	float pixel_lenght = lineHeight/64;
	float x_lenght_ray = 640/(2*n_rays);//No sé como llamar ésto, es simplemente un calculo q hago acá para no hacer muchas veces despues

	pixel.w = x_lenght_ray;
	pixel.h = ceil(pixel_lenght);

	int x_initial_pos;
    if(player.get_direction().y>0){
    	x_initial_pos = x_lenght_ray*(pos_x+n_rays);
    }else{
    	x_initial_pos = 640 - x_lenght_ray*(pos_x+n_rays);
    }
    int num_texture = intersected_object.get_texture();
	pixel.x = x_initial_pos;	
	for(int i=0; i<64; i++){
		int red = textures[num_texture][0][number_line_texture][i]/side_division;
		int green = textures[num_texture][1][number_line_texture][i]/side_division;
		int blue = textures[num_texture][2][number_line_texture][i]/side_division;
		SDL_SetRenderDrawColor(renderer,red , green, blue, SDL_ALPHA_OPAQUE);
	   	pixel.y = initial_position_y + ceil((i*pixel_lenght));
	    SDL_RenderFillRect( renderer, &pixel );    	
	}
}


void Raycasting::calculate_ray_casting(){

    background.show();

    /* Futuro mutex acá (en un thread proceso 
    botones, actualizo la posicion, etc y en otro 
    corro esto, que recibe la posicion, por esta mismma razon
    recibe una copia, así una vez recibida, pueden correr
    ambos en simultaneo)*/
    Coordinates player_coordinates = player.get_coordinates();
    Coordinates player_direction = player.get_direction();
    Camera camera(player_coordinates,player_direction);
	for(int i=-n_rays; i<=n_rays; i++){
		Coordinates ray_direction = camera.calculate_ray_direction(i,n_rays);
		float ray_angle = atan(std::abs((float)i/(float)n_rays));
		Ray ray(ray_angle, ray_direction,player_coordinates,player_direction,map);
		draw(ray.get_colisioned_object(),i);
	}
}