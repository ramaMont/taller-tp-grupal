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

void Texture::show_gun(int frame_gun, int current_gun){
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

void Texture::show_enemy(int state, int frame,int enemy,int pos_x, float distance_player_plane, int number_line_texture){
	
	float lineHeight = (this->height / distance_player_plane);
	int initial_position_y =  -lineHeight/2 + this->height/2;

	float pixel_length = lineHeight/64;

	int x_lenght_ray = this->width/(2*n_rays);//No sé como llamar ésto, es simplemente un calculo q hago acá para no hacer muchas veces despues

	int x_initial_pos = x_lenght_ray*(pos_x+n_rays);


	int height_ray = (int)ceil(pixel_length*64);
	//if(height_ray<height){
		imgPartRect.x = 65*state + number_line_texture; //Desde qué pixel en X quiero
		imgPartRect.y = frame*65;	//Desde qué pixel en Y quiero
		imgPartRect.w = 1; //Cantidad de pixeles en X que tomo
		imgPartRect.h = 64; //Cantidad de pixeles en Y que tomo
		//printf("(int)ceil(pixel_length*64): %i \n",(int)ceil(pixel_length*64) );
	     const SDL_Rect sdlDst = {
	        x_initial_pos, //Posicion inicial de X donde voy a mostrar el pixel
	        initial_position_y, //Posicion inicial de Y donde voy a mostrar el pixel
	        x_lenght_ray, //Cantidad de pixeles en X donde voy a mostrar lo pedido (ancho)
	        height_ray//Cantidad de pixeles en Y donde voy a mostrar lo pedido (alto)
	    };     
	    SDL_RenderCopy(this->renderer, enemies[enemy], &imgPartRect, &sdlDst);
}

void Texture::show(SDL_Texture* texture,int x_pixel_line,int x_initial_pos,int x_lenght_ray, float pixel_length,int initial_position_y){
	int height_ray = (int)ceil(pixel_length*64);
	//if(height_ray<height){
		imgPartRect.x = x_pixel_line; //Desde qué pixel en X quiero
		imgPartRect.y = 0;	//Desde qué pixel en Y quiero
		imgPartRect.w = 1; //Cantidad de pixeles en X que tomo
		imgPartRect.h = 64; //Cantidad de pixeles en Y que tomo
		//printf("(int)ceil(pixel_length*64): %i \n",(int)ceil(pixel_length*64) );
	     const SDL_Rect sdlDst = {
	        x_initial_pos, //Posicion inicial de X donde voy a mostrar el pixel
	        initial_position_y, //Posicion inicial de Y donde voy a mostrar el pixel
	        x_lenght_ray, //Cantidad de pixeles en X donde voy a mostrar lo pedido (ancho)
	        height_ray//Cantidad de pixeles en Y donde voy a mostrar lo pedido (alto)
	    };     
	    SDL_RenderCopy(this->renderer, texture, &imgPartRect, &sdlDst);
}

void Texture::show_wall(int pos_x,float distance_player_plane, int number_line_texture, int texture, bool wall_side_y){

	float lineHeight = (this->height / distance_player_plane);
	float initial_position_y =  -lineHeight/2 + height/2;

	float pixel_length = lineHeight/64;

	float x_lenght_ray = this->width/(2*n_rays);//No sé como llamar ésto, es simplemente un calculo q hago acá para no hacer muchas veces despues

	int x_initial_pos = x_lenght_ray*(pos_x+n_rays);

	int current_texture = 2*texture + wall_side_y;
	show(this->wall_textures[current_texture],number_line_texture,x_initial_pos,x_lenght_ray,pixel_length,initial_position_y);
}

void Texture::show_sprite(int pos_x, float distance_player_plane, int number_line_texture, int texture){

	float lineHeight = (this->height / distance_player_plane);
	float initial_position_y =  -lineHeight/2 + height/2;

	float pixel_length = lineHeight/64;

	float x_lenght_ray = this->width/(2*n_rays);//No sé como llamar ésto, es simplemente un calculo q hago acá para no hacer muchas veces despues

	int x_initial_pos = x_lenght_ray*(pos_x+n_rays);

	show(this->sprites[texture],number_line_texture,x_initial_pos,x_lenght_ray,pixel_length,initial_position_y);
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