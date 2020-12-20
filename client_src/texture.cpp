#include "texture.h"
#include <SDL2/SDL_image.h>
#include <string>

#include <SDL2/SDL.h>

#include <cmath>


void Texture::add_wall_texture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("textures/" + new_texture+".png").c_str());
    wall_textures.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);

    loadedSurface = IMG_Load(("textures/" + new_texture+"_shaded.png").c_str());
    wall_textures.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);

}

void Texture::add_sprite_texture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("textures/" + new_texture+".png").c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 0, 0, 0);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
    sprites.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);	
}

void Texture::add_enemy_texture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("textures/" + new_texture+".png").c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
    enemies.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);		
}

void Texture::add_gun_texture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("textures/" + new_texture+".png").c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
	guns = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);		
}

Texture::Texture(SDL_Renderer* renderer, int height) : renderer(renderer),height(height) {
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
}

Texture::Texture(const Window& window, int n_rays):
	renderer(window.getRenderer()),height(window.get_height()),
	width(window.get_width()),n_rays(n_rays)	{

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

	}


void Texture::show(SDL_Texture* texture,int x_pixel_line,int y_pixel_line,int pos_x, float distance_player_plane){

	float lineHeight = (this->height / distance_player_plane);
	int initial_position_y =  -lineHeight/2 + height/2;

	float pixel_length = lineHeight/64;

	float x_lenght_ray = this->width/(2*n_rays);//No sé como llamar ésto, es simplemente un calculo q hago acá para no hacer muchas veces despues

	int x_initial_pos = x_lenght_ray*(pos_x+n_rays);

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


void Texture::show_weapon(int frame_gun, int current_gun){
		imgPartRect.x = 65*frame_gun; //Desde qué pixel en X quiero
		imgPartRect.y = current_gun*65;	//Desde qué pixel en Y quiero
		imgPartRect.w = 64; //Cantidad de pixeles en X que tomo
		imgPartRect.h = 64; //Cantidad de pixeles en Y que tomo
		//printf("(int)ceil(pixel_length*64): %i \n",(int)ceil(pixel_length*64) );
	     const SDL_Rect sdlDst = {
	        width/2 - 160, //Posicion inicial de X donde voy a mostrar el pixel
	        height - 320, //Posicion inicial de Y donde voy a mostrar el pixel
	        320, //Cantidad de pixeles en X donde voy a mostrar lo pedido (ancho)
	        320//Cantidad de pixeles en Y donde voy a mostrar lo pedido (alto)
	    };     
	    SDL_RenderCopy(this->renderer, guns, &imgPartRect, &sdlDst);
}

void Texture::show_sprites(SDL_Texture* texture,int x_pixel_line,int y_pixel_line,int upper_limit,int pos_x, float distance_player_plane){

	float lineHeight = (this->height / distance_player_plane);
	int initial_position_y =  -lineHeight/2 + height/2;

	float pixel_length = lineHeight/64;

	float x_lenght_ray = this->width/(2*n_rays);//No sé como llamar ésto, es simplemente un calculo q hago acá para no hacer muchas veces despues

	int x_initial_pos = x_lenght_ray*(pos_x+n_rays);

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

void Texture::show_knife(int frame_gun){
	show_weapon(frame_gun,0);
}
void Texture::show_gun(int frame_gun){
	show_weapon(frame_gun,1);
}
void Texture::show_machine_gun(int frame_gun){
	show_weapon(frame_gun,2);
}
void Texture::show_chain_gun(int frame_gun){
	show_weapon(frame_gun,3);
}



void Texture::show_dog(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture){
	show_sprites(this->enemies[2],65*state + number_line_texture,frame*65,32 ,pos_x,distance_player_plane);
}

void Texture::show_guard(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture){
	if(number_line_texture>15 and number_line_texture<49)
		show_sprites(this->enemies[0],65*state + number_line_texture,frame*65,15 ,pos_x,distance_player_plane);
}

void Texture::show_officer(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture){
	if(number_line_texture>15 and number_line_texture<49)		
		show_sprites(this->enemies[1],65*state + number_line_texture,frame*65,12, pos_x,distance_player_plane);
}

void Texture::show_ss(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture){
	if(number_line_texture>0 and number_line_texture<64)		
		show_sprites(this->enemies[3],65*state + number_line_texture,frame*65,8, pos_x,distance_player_plane);
}

void Texture::show_mutant(int state, int frame,int pos_x, float distance_player_plane, int number_line_texture){
	if(number_line_texture>15 and number_line_texture<49)	
		show_sprites(this->enemies[4],65*state + number_line_texture,frame*65,17, pos_x,distance_player_plane);
}



void Texture::show_wall(int pos_x,float distance_player_plane, int number_line_texture, int texture, bool wall_side_y){
	int current_texture = 2*texture + wall_side_y;
	show(this->wall_textures[current_texture],number_line_texture,0,pos_x,distance_player_plane);
}


//0: barril; 1: columna; 2: lampara
void Texture::show_sprite(int pos_x, float distance_player_plane, int number_line_texture, int texture){
	if(texture==0){
		if(number_line_texture>15 and number_line_texture<48)	
			show_sprites(this->sprites[texture],number_line_texture,0,31,pos_x,distance_player_plane);
	}
	else if(texture==1){
		if(number_line_texture>15)	
			show_sprites(this->sprites[texture],number_line_texture,0,0,pos_x,distance_player_plane);		
	}else if(texture==2){
		show(this->sprites[texture],number_line_texture,0,pos_x,distance_player_plane);
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
}