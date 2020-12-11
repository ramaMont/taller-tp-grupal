#include <math.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "ray_casting.h"
#include "camera.h"
#include "ray.h"

void Raycasting::load_wall_texture(std::string file_name,int number_texture){
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

void Raycasting::load_ohter_texture(std::string file_name,int number_texture){
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

void Raycasting::load_guard_texture(std::string file_name,int number_texture){
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

void Raycasting::init_textures(){

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

	load_guard_texture("front_guard.mat",0);
	load_guard_texture("side_guard.mat",1);
	load_guard_texture("back_guard.mat",2);

}


Raycasting::Raycasting(std::vector<Sprite*> &sprites, \
					Jugador &a_player,Mapa &a_map,const Window &window)
    : player(a_player), map(a_map),
    renderer(window.getRenderer()),
    height(window.get_height()),
    widht(window.get_width()),
    background(window),n_rays(160),
    sprites(sprites) 
    {
    init_textures();
}

void Raycasting::init_pixel(SDL_Rect &pixel, const float &pixel_lenght, const int pos_x){
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

void Raycasting::draw_sprites(int pos_x, float distance_player_plane, int number_line_texture, int texture){
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

void Raycasting::draw_wall(int pos_x,float distance_player_plane, int number_line_texture, int texture, int side_division){


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


static void sort_vector(std::vector<Sprite*> &spotted_sprites){
	std::sort(spotted_sprites.begin(),
	          spotted_sprites.end(),
	          [](const Sprite* sprite, const Sprite* another_sprite)
	{
	    return sprite->get_distance_player_plane() > another_sprite->get_distance_player_plane();
	});	
}

void Raycasting::calculate_ray_casting(){

    background.show();

	//Desactivo todos los sprites que fueron vistos el anterior frame
	for(unsigned int i=0; i<sprites.size(); i++){
		sprites[i]->disable_spotted();
	}
    Coordinates player_position = player.get_coordinates();
    Coordinates player_direction = player.get_direction();
    Camera camera(player_position,player_direction);
	std::vector<float> distances;
	for(int i=-n_rays; i<=n_rays; i++){
		Coordinates ray_direction = camera.calculate_ray_direction(i,n_rays);
		float ray_angle = atan(std::abs((float)i/(float)n_rays));
		Ray ray(ray_angle, ray_direction,distances,player_position,player_direction,map,i);
		Intersected_object intersected_object = ray.get_colisioned_objects();
		float distance_player_plane = intersected_object.get_distance_player_plane();
		int number_line_texture = intersected_object.get_number_line_texture();
		int texture = intersected_object.get_texture();
		int side_division = intersected_object.get_side_division();
		draw_wall(i,distance_player_plane,number_line_texture,texture, side_division);
	}


	std::vector<Sprite*> spotted_sprites;
	for(unsigned int i=0; i<sprites.size(); i++){
		if(sprites[i]->is_spotted()){
			spotted_sprites.push_back(sprites[i]);
		}
	}


	for(unsigned int j=0; j<spotted_sprites.size(); j++){
		for(int i=-2*n_rays; i<=2*n_rays; i++){
			Coordinates ray_direction = camera.calculate_ray_direction(i,n_rays);
			spotted_sprites[j]->update_distance_to_closest_ray(i,ray_direction);
		}
		spotted_sprites[j]->set_distance(camera.get_camera_plane());
	}

	sort_vector(spotted_sprites);	

	for(unsigned int j=0; j<spotted_sprites.size(); j++){
		spotted_sprites[j]->draw(this,distances,n_rays);
	}


}