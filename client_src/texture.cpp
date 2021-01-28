#include "texture.h"
#include <SDL2/SDL_image.h>
#include <string>

#include <SDL2/SDL.h>
#include <cmath>

#include <iostream>
#include<string>

void Texture::add_wall_texture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/" + new_texture+".png").c_str());
    wall_textures.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);

    loadedSurface = IMG_Load(("../data/textures/" + new_texture+"_shaded.png").c_str());
    wall_textures.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);

}

void Texture::add_sprite_texture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/" + new_texture+".png").c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 0, 0, 0);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
    sprites.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);	
}

void Texture::add_shooting_effect_texture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/" + new_texture+".png").c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
    shooting_effect.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);		
}

void Texture::add_enemy_texture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/" + new_texture+".png").c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
    enemies.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);		
}

void Texture::add_gun_texture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/" + new_texture+".png").c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
	guns = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);		
}

void Texture::add_door_textures(){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/door.png"));
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
	door = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);			
}

void Texture::add_life_bar_texture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/" + new_texture+".png").c_str());
	life_bar = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);		
}

Texture::Texture(const Window& window):
	renderer(window.getRenderer()),height(window.get_height()-112),
	width(window.get_width()){

	add_wall_texture("greystone");
	add_wall_texture("bluestone");
	add_wall_texture("purplestone");
	add_wall_texture("colorstone");
	add_wall_texture("eagle");
	add_wall_texture("mossy");
	add_wall_texture("redbrick");
	add_wall_texture("wood");

	add_sprite_texture("barrel");
	add_sprite_texture("pillar");
	add_sprite_texture("greenlight");
	add_sprite_texture("trophie");
	add_sprite_texture("rocket_launcher");
	add_sprite_texture("medicine");
	add_sprite_texture("machine_gun");
	add_sprite_texture("key");
	add_sprite_texture("food");
	add_sprite_texture("fire_canon");
	add_sprite_texture("bullets");	
	add_sprite_texture("table");	

	add_enemy_texture("guard_pos");
	add_enemy_texture("officer_pos");
	add_enemy_texture("dog_pos");
	add_enemy_texture("ss_pos");
	add_enemy_texture("mutant_pos");

	add_shooting_effect_texture("guard_shooting");

	add_gun_texture("guns");
	add_door_textures();
	add_life_bar_texture("life_bar");

	this->x_lenght_ray = ceil((float)this->width/(window.get_resolution_width()));//No sé como llamar ésto, es simplemente un calculo q hago acá para no hacer muchas veces despues


	if (TTF_Init() < 0) {
	    printf("error inicializacionnnn\n");
	}


	this->Sans = TTF_OpenFont("../data/comic-sans.ttf", 24); //this opens a font style and sets a size

	if(!Sans){
		printf("no encuentro la fooont\n");
	}
}




void Texture::show_life_bar(unsigned int score, int lives, int health, int ammo){
		imgPartRect.x = 0; //Desde qué pixel en X quiero
		imgPartRect.y = 0;	//Desde qué pixel en Y quiero
		imgPartRect.w = 1097; //Cantidad de pixeles en X que tomo
		imgPartRect.h = 127; //Cantidad de pixeles en Y que tomo

	    const SDL_Rect sdlDst = {
	        0, //Posicion inicial de X donde voy a mostrar el pixel
	        height, //Posicion inicial de Y donde voy a mostrar el pixel
	        width, //Cantidad de pixeles en X donde voy a mostrar lo pedido (ancho)
	        112//Cantidad de pixeles en Y donde voy a mostrar lo pedido (alto)
	    };   
	    SDL_RenderCopy(this->renderer, life_bar, &imgPartRect, &sdlDst);	

	    show_text(std::to_string(score).c_str(),20,80,170);
	    show_text(std::to_string(lives).c_str(),40,80,250);	    

	    std::string text_health = std::to_string(health).c_str();
	    if(strlen(text_health.c_str())>2){
	    	show_text(text_health,17,80,390);	    
	    }else{
	    	show_text(text_health,20,80,390);	    	    	
	    }
	    show_text(std::to_string(ammo).c_str(),20,80,480);	    
}

void Texture::show_text(std::string text, int letter_width, int letter_height, int x_pos){

	SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, text.c_str(), White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

	int len_message = letter_width*(int)strlen(text.c_str());

	const SDL_Rect sdlDst = {
	    x_pos - len_message, //Posicion inicial de X donde voy a mostrar el pixel
	    height+25, //Posicion inicial de Y donde voy a mostrar el pixel
	    len_message, //Cantidad de pixeles en X donde voy a mostrar lo pedido (ancho)
	    letter_height//Cantidad de pixeles en Y donde voy a mostrar lo pedido (alto)
	};
	//Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understand

	//Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes

	SDL_RenderCopy(renderer, Message, NULL, &sdlDst); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
	//Don't forget to free your surface and texture
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);	
}

void Texture::show_weapon(int frame_gun, int current_gun, int left_start_texture, int right_end_texture){
	int widht_drawable_pixel = right_end_texture - left_start_texture;

	int first_x_pixel = 65*frame_gun + left_start_texture;
	int cant_x_pixels = widht_drawable_pixel;
	int first_y_pixel = current_gun*65;
	int cant_y_pixels = 64;

	int windows_x_pos = width/2 - (65/2 - left_start_texture)*4;
	int windows_y_pos = height - 320;
	int length_x = widht_drawable_pixel*5;
	int lenght_y = 320;

	generic_show(guns,first_x_pixel,cant_x_pixels,first_y_pixel,cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}

void Texture::show_knife(int frame_gun){
		show_weapon(frame_gun,0,27,53);
}
void Texture::show_gun(int frame_gun){
		show_weapon(frame_gun,1,20,47);
}
void Texture::show_machine_gun(int frame_gun){
		show_weapon(frame_gun,2,13,52);
}
void Texture::show_chain_gun(int frame_gun){
		show_weapon(frame_gun,3,7,59);
}


void Texture::generic_show(SDL_Texture* texture, int first_x_pixel, int cant_x_pixels, int first_y_pixel, int cant_y_pixel,\
		int windows_x_pos, int length_x, int windows_y_pos, int length_y){

		imgPartRect.x = first_x_pixel; //Desde qué pixel en X quiero
		imgPartRect.w = cant_x_pixels; //Cantidad de pixeles en X que tomo
		imgPartRect.y = first_y_pixel;	//Desde qué pixel en Y quiero
		imgPartRect.h = cant_y_pixel; //Cantidad de pixeles en Y que tomo
	     const SDL_Rect sdlDst = {
	        windows_x_pos, //Posicion inicial de X donde voy a mostrar el pixel
	        windows_y_pos, //Posicion inicial de Y donde voy a mostrar el pixel
	        length_x, //Cantidad de pixeles en X donde voy a mostrar lo pedido (ancho)
	        length_y//Cantidad de pixeles en Y donde voy a mostrar lo pedido (alto)
	    };     
	    SDL_RenderCopy(this->renderer, texture, &imgPartRect, &sdlDst);

}

void Texture::show_enemy(SDL_Texture* texture, int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture){
	float lineHeight = (this->height / distance_player_plane);
	int initial_position_y =  -lineHeight/2 + this->height/2;
	float pixel_length = lineHeight/64;
	int x_initial_pos = x_lenght_ray*x_pixel;
	int height_ray = (int)ceil((pixel_length)*64);


	int first_x_pixel = 65*state + number_line_texture;
	int cant_x_pixels = 1;
	int first_y_pixel = frame*65;
	int cant_y_pixels = 64;

	int windows_x_pos = x_initial_pos;
	int windows_y_pos = initial_position_y;
	int length_x = x_lenght_ray;
	int lenght_y = height_ray;

	generic_show(texture,first_x_pixel,cant_x_pixels,first_y_pixel,cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}


void Texture::show_guard(int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture, bool is_shooting){
	show_enemy(this->enemies[0], state, frame, x_pixel, distance_player_plane, number_line_texture);
	if(is_shooting)
		show_enemy(this->shooting_effect[0],state,0,x_pixel,distance_player_plane, number_line_texture);
}

void Texture::show_officer(int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture, bool is_shooting){
	show_enemy(this->enemies[1], state, frame, x_pixel, distance_player_plane, number_line_texture);
}

void Texture::show_dog(int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture, bool is_shooting){
	show_enemy(this->enemies[2], state, frame, x_pixel, distance_player_plane, number_line_texture);
}

void Texture::show_ss(int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture, bool is_shooting){
	show_enemy(this->enemies[3], state, frame, x_pixel, distance_player_plane, number_line_texture);
}

void Texture::show_mutant(int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture, bool is_shooting){
	show_enemy(this->enemies[4], state, frame, x_pixel, distance_player_plane, number_line_texture);
}


void Texture::show_wall(SDL_Texture* texture,int x_pixel,float distance_player_plane, int number_line_texture){
	float lineHeight = (this->height / distance_player_plane);
	int initial_position_y =  -lineHeight/2 + height/2;

	float pixel_length = lineHeight/64;

	int x_initial_pos = x_lenght_ray*x_pixel;

	int height_ray = (int)ceil(pixel_length*64);	

	int first_x_pixel = number_line_texture;
	int cant_x_pixels = 1;
	int first_y_pixel = 0;
	int cant_y_pixels = 64;

	int windows_x_pos = x_initial_pos;
	int windows_y_pos = initial_position_y;
	int length_x = x_lenght_ray;
	int lenght_y = height_ray;

	generic_show(texture,first_x_pixel,cant_x_pixels,first_y_pixel,cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}


void Texture::show_wall_greystone(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = wall_side_y;
	show_wall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::show_wall_bluestone(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*1 + wall_side_y;
	show_wall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::show_wall_purplestone(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*2 + wall_side_y;
	show_wall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::show_wall_colorstone(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*3 + wall_side_y;
	show_wall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::show_wall_eagle(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*4 + wall_side_y;
	show_wall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::show_wall_mossy(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*5 + wall_side_y;
	show_wall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::show_wall_redbrick(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*6 + wall_side_y;
	show_wall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::show_wall_wood(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*7 + wall_side_y;
	show_wall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::show_door(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	show_wall(door, x_pixel, distance_player_plane, number_line_texture);
}

static void sort_values(int &first_value, int &second_value){
	if(first_value>second_value){
		int temporal_value = first_value;
		first_value = second_value;
		second_value = temporal_value;
	}
}

void Texture::show_sprite(int first_x_pixel,int first_number_line_texture,int last_x_pixel, int last_number_line_texture,float distance_player_plane,int texture){
	sort_values(first_x_pixel,last_x_pixel);
	sort_values(first_number_line_texture,last_number_line_texture);

	float lineHeight = (this->height / distance_player_plane);
	int initial_position_y =  -lineHeight/2 + height/2;
	float pixel_length = lineHeight/64;
	int x_initial_pos = x_lenght_ray*first_x_pixel;
	int height_ray = (int)ceil((pixel_length)*64);

	printf("first_number_line_texture %i,  last_number_line_texture %i \n first_x_pixel %i, last_x_pixel %i\n\n",first_number_line_texture, last_number_line_texture, first_x_pixel, last_x_pixel);
	
	generic_show(this->sprites[texture],first_number_line_texture, last_number_line_texture - first_number_line_texture,0,64,\
		x_initial_pos,(int)x_lenght_ray*(last_x_pixel - first_x_pixel),initial_position_y,height_ray);
}

Texture::~Texture() {
	int cant_textures = wall_textures.size();
	for(int i=0; i<cant_textures;i++){
		SDL_DestroyTexture(wall_textures[i]);
	}

	cant_textures = sprites.size();
	for(int i=0; i<cant_textures;i++){
		SDL_DestroyTexture(sprites[i]);
	}

	cant_textures = enemies.size();
	for(int i=0; i<cant_textures;i++){
		SDL_DestroyTexture(enemies[i]);
	}	

	SDL_DestroyTexture(guns);
}