#include <math.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

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

}


Raycasting::Raycasting(std::vector<Barrel*> &sprites, \
					Jugador &a_player,Mapa &a_map,const Window &window)
    : player(a_player), map(a_map),
    renderer(window.getRenderer()),
    background(window), sprites(sprites)
    {
    h = 480;
    n_rays = 160;
    init_textures();
}

void Raycasting::draw_barrel(Sprite sprite, int pos_x, int num_pixel, int texture){
	float distance_player_plane = sprite.get_distance_player_plane();
	float lineHeight = (h / distance_player_plane);
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

	pixel.x = x_initial_pos;
	for(int i=0; i<64; i++){
		int red = other_textures[texture][0][num_pixel][i];
		int green = other_textures[texture][1][num_pixel][i];
		int blue = other_textures[texture][2][num_pixel][i];
		if((red==0) and (green==0) and (blue==0)){
		}else{
			SDL_SetRenderDrawColor(renderer,red , green, blue, SDL_ALPHA_OPAQUE);
			SDL_RenderFillRect( renderer, &pixel );
		}
	   	pixel.y = initial_position_y + ceil((i*pixel_lenght));    	
	}

}

void Raycasting::draw_wall(Intersected_object intersected_object, int pos_x){

	float distance_player_plane = intersected_object.get_distance_player_plane();
	int number_line_texture = intersected_object.get_number_line_texture();
	int side_division = intersected_object.get_side_division();
	int num_texture = intersected_object.get_texture();

	float lineHeight = (h / distance_player_plane);
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
	pixel.x = x_initial_pos;	
	for(int i=0; i<64; i++){
		int red = wall_textures[num_texture][0][number_line_texture][i]/side_division;
		int green = wall_textures[num_texture][1][number_line_texture][i]/side_division;
		int blue = wall_textures[num_texture][2][number_line_texture][i]/side_division;
		SDL_SetRenderDrawColor(renderer,red , green, blue, SDL_ALPHA_OPAQUE);
	   	pixel.y = initial_position_y + ceil((i*pixel_lenght));
	    SDL_RenderFillRect( renderer, &pixel );    	
	}
}

void Raycasting::draw(int pos_x){

	float initial_position_y =  -120/2 + h/2;

	SDL_Rect pixel;

	float pixel_lenght = 128/64;
	float x_lenght_ray = 640/(2*n_rays);//No sé como llamar ésto, es simplemente un calculo q hago acá para no hacer muchas veces despues

	pixel.w = x_lenght_ray;
	pixel.h = ceil(pixel_lenght);

	int x_initial_pos;
    if(player.get_direction().y>0){
    	x_initial_pos = x_lenght_ray*(pos_x+n_rays);
    }else{
    	x_initial_pos = 640 - x_lenght_ray*(pos_x+n_rays);
    }
	pixel.x = x_initial_pos;	
	for(int i=0; i<64; i++){
		SDL_SetRenderDrawColor(renderer,0xff , 0xff, 0xff, SDL_ALPHA_OPAQUE);
	   	pixel.y = initial_position_y + ceil((i*pixel_lenght));
	    SDL_RenderFillRect( renderer, &pixel );    	
	}
}


void Raycasting::calculate_ray_casting(){

    background.show();

	//Desactivo todos los sprites que fueron vistos el anterior frame
	for(unsigned int i=0; i<sprites.size(); i++){
		sprites[i]->disable_spotted();
	}

    Coordinates player_coordinates = player.get_coordinates();
    Coordinates player_direction = player.get_direction();
    Camera camera(player_coordinates,player_direction);
	std::vector<float> distances;
	for(int i=-n_rays; i<=n_rays; i++){
		Coordinates ray_direction = camera.calculate_ray_direction(i,n_rays);
		float ray_angle = atan(std::abs((float)i/(float)n_rays));
		Ray ray(ray_angle, ray_direction,player_coordinates,player_direction,map,i);
		draw_wall(ray.get_colisioned_objects(distances),i);
	}


	std::vector<Sprite> spotted_sprites;
	for(unsigned int i=0; i<sprites.size(); i++){
		if(sprites[i]->is_spotted()){
			Sprite sprite(sprites[i]);
			spotted_sprites.push_back(sprite);
		}
	}

	for(unsigned int j=0; j<spotted_sprites.size(); j++){
		for(int i=-n_rays; i<=n_rays; i++){
			Coordinates ray_direction = camera.calculate_ray_direction(i,n_rays);
			spotted_sprites[j].update_distance_to_closest_ray(i,ray_direction,player_coordinates);
		}
		//spotted_sprites[j].set_center_ray(camera);
		spotted_sprites[j].set_distance(player_coordinates, camera.get_camera_plane());

		int center_ray = spotted_sprites[j].get_centered_ray();
		int cant_rays= spotted_sprites[j].get_cant_rays();
		int first_ray = center_ray - cant_rays/2;
		int texture = spotted_sprites[j].get_texture();
		for(int i=0 ; i<cant_rays ; i++){
			int num_pixel = i*64/cant_rays;
			if(distances[first_ray + i+ n_rays]>spotted_sprites[j].get_distance_player_plane())
				draw_barrel(spotted_sprites[j], first_ray + i, num_pixel,texture);
		}
	}


}