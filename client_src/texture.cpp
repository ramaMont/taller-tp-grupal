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

	add_enemy_texture("guard_pos");
	add_enemy_texture("officer_pos");
	add_enemy_texture("dog_pos");
	add_enemy_texture("ss_pos");
	add_enemy_texture("mutant_pos");

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


void Texture::show(SDL_Texture* texture,int x_pixel_line,int y_pixel_line,int x_pixel, float distance_player_plane){

	float lineHeight = (this->height / distance_player_plane);
	int initial_position_y =  -lineHeight/2 + height/2;

	float pixel_length = lineHeight/64;

	int x_initial_pos = x_lenght_ray*x_pixel;

	int height_ray = (int)ceil(pixel_length*64);
	//if(height_ray<height){
		imgPartRect.x = x_pixel_line; //Desde qué pixel en X quiero
		imgPartRect.y = y_pixel_line;	//Desde qué pixel en Y quiero
		imgPartRect.w = 1; //Cantidad de pixeles en X que tomo
		imgPartRect.h = 64; //Cantidad de pixeles en Y que tomo
		//printf("(int)ceil(pixel_length*64): %i \n",(int)ceil(pixel_length*64) );
	     const SDL_Rect sdlDst = {
	        x_initial_pos, //Posicion inicial de X donde voy a mostrar el pixel
	        initial_position_y, //Posicion inicial de Y donde voy a mostrar el pixel
	        (int)x_lenght_ray, //Cantidad de pixeles en X donde voy a mostrar lo pedido (ancho)
	        height_ray//Cantidad de pixeles en Y donde voy a mostrar lo pedido (alto)
	    };     
	    SDL_RenderCopy(this->renderer, texture, &imgPartRect, &sdlDst);
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


void Texture::show_weapon(int frame_gun, int current_gun, int left_start_texture, int right_end_texture){
		imgPartRect.x = 65*frame_gun + left_start_texture; //Desde qué pixel en X quiero
		imgPartRect.y = current_gun*65;	//Desde qué pixel en Y quiero
		imgPartRect.w = right_end_texture-left_start_texture; //Cantidad de pixeles en X que tomo
		imgPartRect.h = 64; //Cantidad de pixeles en Y que tomo

		int widht_drawable_pixel = right_end_texture - left_start_texture;
	    const SDL_Rect sdlDst = {
	        width/2 - (65/2 - left_start_texture)*4, //Posicion inicial de X donde voy a mostrar el pixel
	        height - 320, //Posicion inicial de Y donde voy a mostrar el pixel
	        widht_drawable_pixel*5, //Cantidad de pixeles en X donde voy a mostrar lo pedido (ancho)
	        320//Cantidad de pixeles en Y donde voy a mostrar lo pedido (alto)
	    };   
	    SDL_RenderCopy(this->renderer, guns, &imgPartRect, &sdlDst);
}

void Texture::show_sprites(SDL_Texture* texture,int x_pixel_line,int y_pixel_line,int upper_limit,int x_pixel, float distance_player_plane){

	float lineHeight = (this->height / distance_player_plane);
	int initial_position_y =  -lineHeight/2 + height/2;

	float pixel_length = lineHeight/64;

	int x_initial_pos = x_lenght_ray*x_pixel;

	int height_ray = (int)ceil((pixel_length)*64);
	//if(height_ray<height){
		imgPartRect.x = x_pixel_line; //Desde qué pixel en X quiero
		imgPartRect.y = y_pixel_line +  upper_limit;	//Desde qué pixel en Y quiero
		imgPartRect.w = 1; //Cantidad de pixeles en X que tomo
		imgPartRect.h = 64 - upper_limit; //Cantidad de pixeles en Y que tomo
		//printf("(int)ceil(pixel_length*64): %i \n",(int)ceil(pixel_length*64) );
	     const SDL_Rect sdlDst = {
	        x_initial_pos, //Posicion inicial de X donde voy a mostrar el pixel
	        initial_position_y + (int)(pixel_length*upper_limit), //Posicion inicial de Y donde voy a mostrar el pixel
	        (int)x_lenght_ray, //Cantidad de pixeles en X donde voy a mostrar lo pedido (ancho)
	        height_ray - (int)(pixel_length*upper_limit)//Cantidad de pixeles en Y donde voy a mostrar lo pedido (alto)
	    };     
	    SDL_RenderCopy(this->renderer, texture, &imgPartRect, &sdlDst);
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



void Texture::show_dog(int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture){
	show_sprites(this->enemies[2],65*state + number_line_texture,frame*65,32 ,x_pixel,distance_player_plane);
}

void Texture::show_guard(int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture){
	if(number_line_texture>15 and number_line_texture<49)
		show_sprites(this->enemies[0],65*state + number_line_texture,frame*65,15 ,x_pixel,distance_player_plane);
}

void Texture::show_officer(int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture){
	if(number_line_texture>15 and number_line_texture<49)		
		show_sprites(this->enemies[1],65*state + number_line_texture,frame*65,12, x_pixel,distance_player_plane);
}

void Texture::show_ss(int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture){
	if(number_line_texture>0 and number_line_texture<64)		
		show_sprites(this->enemies[3],65*state + number_line_texture,frame*65,8, x_pixel,distance_player_plane);
}

void Texture::show_mutant(int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture){
	if(number_line_texture>15 and number_line_texture<49)	
		show_sprites(this->enemies[4],65*state + number_line_texture,frame*65,17, x_pixel,distance_player_plane);
}


void Texture::show_wall_greystone(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = wall_side_y;
	show(this->wall_textures[current_texture],number_line_texture,0,x_pixel,distance_player_plane);
}

void Texture::show_wall_bluestone(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*1 + wall_side_y;
	show(this->wall_textures[current_texture],number_line_texture,0,x_pixel,distance_player_plane);
}

void Texture::show_wall_purplestone(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*2 + wall_side_y;
	show(this->wall_textures[current_texture],number_line_texture,0,x_pixel,distance_player_plane);
}

void Texture::show_wall_colorstone(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*3 + wall_side_y;
	show(this->wall_textures[current_texture],number_line_texture,0,x_pixel,distance_player_plane);
}

void Texture::show_wall_eagle(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*4 + wall_side_y;
	show(this->wall_textures[current_texture],number_line_texture,0,x_pixel,distance_player_plane);
}

void Texture::show_wall_mossy(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*5 + wall_side_y;
	show(this->wall_textures[current_texture],number_line_texture,0,x_pixel,distance_player_plane);
}

void Texture::show_wall_redbrick(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*6 + wall_side_y;
	show(this->wall_textures[current_texture],number_line_texture,0,x_pixel,distance_player_plane);
}

void Texture::show_wall_wood(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*7 + wall_side_y;
	show(this->wall_textures[current_texture],number_line_texture,0,x_pixel,distance_player_plane);
}

void Texture::show_door(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	show(this->door,number_line_texture,0,x_pixel,distance_player_plane);
}

//0: barril; 1: columna; 2: lampara
void Texture::show_sprite(int x_pixel, float distance_player_plane, int number_line_texture, int texture){
	if(texture==0){
		if(number_line_texture>15 and number_line_texture<48)	
			show_sprites(this->sprites[texture],number_line_texture,0,31,x_pixel,distance_player_plane);
	}
	else if(texture==1){
		if(number_line_texture>15)	
			show_sprites(this->sprites[texture],number_line_texture,0,0,x_pixel,distance_player_plane);		
	}else if(texture==2){
		show(this->sprites[texture],number_line_texture,0,x_pixel,distance_player_plane);
	}
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