#include "texture.h"
#include <SDL2/SDL_image.h>
#include <string>

#include <SDL2/SDL.h>
#include <cmath>

#include <iostream>
#include<string>

#include "SpriteValues.h"

void Texture::addWallTexture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/" + new_texture+".png").c_str());
    wall_textures.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);

    loadedSurface = IMG_Load(("../data/textures/" + new_texture+"_shaded.png").c_str());
    wall_textures.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);
}

void Texture::addSpriteTexture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/" + new_texture+".png").c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 0, 0, 0);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
	sprites.insert(std::pair<int,SDL_Texture*>(texture_values.at(new_texture),SDL_CreateTextureFromSurface(renderer, loadedSurface)));
	SDL_FreeSurface(loadedSurface);	
}

void Texture::addShootingEffectTexture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/" + new_texture+".png").c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
    shooting_effect.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);		
}

void Texture::addEnemyTexture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/" + new_texture+".png").c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
    enemies.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);		
}

void Texture::addDeadEnemyTexture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/dead_enemies/" + new_texture+".png").c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
    sprites.insert(std::pair<int,SDL_Texture*>(texture_values.at(new_texture),SDL_CreateTextureFromSurface(renderer, loadedSurface)));
	SDL_FreeSurface(loadedSurface);		
}

void Texture::addGunTexture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/" + new_texture+".png").c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
	guns = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);		
}

void Texture::addDoorTextures(){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/door.png"));
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
	door = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);			
}

void Texture::addLifeBarTexture(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/bar_textures/" + new_texture+".png").c_str());
	life_bar = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);		
}

void Texture::addFaceHealth(){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/bar_textures/face_health.png"));
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 255, 255, 255);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
	face_health = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);		

}

void Texture::addBarGuns(std::string new_texture){
    SDL_Surface* loadedSurface = IMG_Load(("../data/textures/bar_textures/" + new_texture+".png").c_str());
    bar_guns.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);		

}

void Texture::addEndingBackground(){
    SDL_Surface* loadedSurface = IMG_Load(("../data/endig_background.png"));
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
	endig_background = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);		

}

Texture::Texture(const Window& window):
	renderer(window.getRenderer()),height(window.getHeight()-112),
	width(window.getWidth()){

	addWallTexture("greystone");
	addWallTexture("bluestone");
	addWallTexture("purplestone");
	addWallTexture("colorstone");
	addWallTexture("eagle");
	addWallTexture("mossy");
	addWallTexture("redbrick");
	addWallTexture("wood");

	addSpriteTexture("barrel");
	addSpriteTexture("pillar");
	addSpriteTexture("greenlight");
	addSpriteTexture("trophie");
	addSpriteTexture("rocket_launcher");
	addSpriteTexture("medicine");
	addSpriteTexture("machine_gun");
	addSpriteTexture("key");
	addSpriteTexture("food");
	addSpriteTexture("fire_canon");
	addSpriteTexture("bullets");	
	addSpriteTexture("table");	
	addSpriteTexture("rocket");

	addEnemyTexture("guard_pos");
	addEnemyTexture("officer_pos");
	addEnemyTexture("ss_pos");
	addEnemyTexture("mutant_pos");
	addEnemyTexture("dog_pos");

	addDeadEnemyTexture("dead_dog");
	addDeadEnemyTexture("dead_guard");
	addDeadEnemyTexture("dead_officer");
	addDeadEnemyTexture("dead_ss");
	addDeadEnemyTexture("dead_mutant");

	addShootingEffectTexture("guard_shooting");
	addShootingEffectTexture("officer_shooting");
	addShootingEffectTexture("ss_shooting");
	addShootingEffectTexture("ss_shooting"); //Acá despues va el de mutant

	addGunTexture("guns");

	addDoorTextures();

	addLifeBarTexture("life_bar");

	addBarGuns("knife");
	addBarGuns("gun");
	addBarGuns("machine_gun");
	addBarGuns("chain_gun");
	addBarGuns("rocket_launcher");

	addFaceHealth();

	addEndingBackground();

	this->x_lenght_ray = ceil((float)this->width/(window.getResolutionWidth()));//No sé como llamar ésto, es simplemente un calculo q hago acá para no hacer muchas veces despues


	if (TTF_Init() < 0) {
	    printf("error inicializacionnnn\n");
	}


	this->Sans = TTF_OpenFont("../data/comic-sans.ttf", 24); //this opens a font style and sets a size

	if(!Sans){
		printf("no encuentro la fooont\n");
	}
}


void Texture::showFaceHealth(int portion_health){

	int first_x_pixel = 0;//Desde qué pixel en X quiero
	int cant_x_pixels = 145;
	int first_y_pixel = 0;
	int cant_y_pixels = 190;

	int windows_x_pos = width/2 - 55;//Posicion inicial de X donde voy a mostrar el pixel
	int windows_y_pos = height + 5;//		
	int length_x = 63;
	int lenght_y = 100;

	if(portion_health==1){
		first_x_pixel = 433;
		first_y_pixel = 190;
	}else if(portion_health==2){
		first_x_pixel = 289;
		first_y_pixel = 190;
	}else if(portion_health==3){
		first_x_pixel = 144;
		first_y_pixel = 190;
	}else if(portion_health==4){
		first_x_pixel = 0;
		first_y_pixel = 190;
	}else if(portion_health==5){
		first_x_pixel = 433;
		first_y_pixel = 0;
	}else if(portion_health==6){
		first_x_pixel = 289;
		first_y_pixel = 0;
	}else if(portion_health==7){
		first_x_pixel = 144;
		first_y_pixel = 0;
	}else{
		first_x_pixel = 0;
		first_y_pixel = 0;
	}
	genericShow(face_health,first_x_pixel,cant_x_pixels,first_y_pixel,cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}

void Texture::showLifeBar(unsigned int score, int lives,int health ,int portion_health, int ammo, bool has_key_1, bool has_key_2){
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

	    showText(std::to_string(score).c_str(),20,80,170);
	    showText(std::to_string(lives).c_str(),40,80,250);	    

	    std::string text_health = std::to_string(health).c_str();
	    if(strlen(text_health.c_str())>2){
	    	showText(text_health,17,80,390);	    
	    }else{
	    	showText(text_health,20,80,390);	    	    	
	    }
	    showText(std::to_string(ammo).c_str(),20,80,480);	    

	    showFaceHealth(portion_health);
}

void Texture::showText(std::string text, int letter_width, int letter_height, int x_pos){

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

void Texture::showWeapon(int frame_gun, int current_gun){
	//int widht_drawable_pixel = right_end_texture - left_start_texture;

	int first_x_pixel = 129*frame_gun;
	int cant_x_pixels = 128;
	int first_y_pixel = current_gun*129;
	int cant_y_pixels = 128;

	int windows_x_pos = width/2 - 65;
	int windows_y_pos = height - 160;
	int length_x = 65*2;
	int lenght_y = 160;

	genericShow(guns,first_x_pixel,cant_x_pixels,first_y_pixel,cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}

void Texture::showKnife(int frame_gun){
		//showWeapon(frame_gun,0,27,53);
		showWeapon(frame_gun,0);

		int first_x_pixel = 0;//Desde qué pixel en X quiero
		int cant_x_pixels = 450;
		int first_y_pixel = 0;
		int cant_y_pixels = 150;

		int windows_x_pos = width - 130;//Posicion inicial de X donde voy a mostrar el pixel
		int windows_y_pos = height + 15;//		
		int length_x = 120;
		int lenght_y = 80;
		genericShow(this->bar_guns[0],first_x_pixel,cant_x_pixels,first_y_pixel,cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}
void Texture::showGun(int frame_gun){
		//showWeapon(frame_gun,1,20,47);
		showWeapon(frame_gun,1);

		int first_x_pixel = 0;//Desde qué pixel en X quiero
		int cant_x_pixels = 400;
		int first_y_pixel = 0;
		int cant_y_pixels = 190;

		int windows_x_pos = width - 130;//Posicion inicial de X donde voy a mostrar el pixel
		int windows_y_pos = height + 15;//		
		int length_x = 120;
		int lenght_y = 80;
		genericShow(this->bar_guns[1],first_x_pixel,cant_x_pixels,first_y_pixel,cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}
void Texture::showMachineGun(int frame_gun){
		//showWeapon(frame_gun,2,13,52);
		showWeapon(frame_gun,2);

		int first_x_pixel = 0;//Desde qué pixel en X quiero
		int cant_x_pixels = 460;
		int first_y_pixel = 0;
		int cant_y_pixels = 170;

		int windows_x_pos = width - 130;//Posicion inicial de X donde voy a mostrar el pixel
		int windows_y_pos = height + 15;//		
		int length_x = 120;
		int lenght_y = 80;
		genericShow(this->bar_guns[2],first_x_pixel,cant_x_pixels,first_y_pixel,cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}
void Texture::showChainGun(int frame_gun){
		//showWeapon(frame_gun,3,7,59);
		showWeapon(frame_gun,3);

		int first_x_pixel = 0;//Desde qué pixel en X quiero
		int cant_x_pixels = 490;
		int first_y_pixel = 0;
		int cant_y_pixels = 220;

		int windows_x_pos = width - 130;//Posicion inicial de X donde voy a mostrar el pixel
		int windows_y_pos = height + 15;//		
		int length_x = 120;
		int lenght_y = 80;
		genericShow(this->bar_guns[3],first_x_pixel,cant_x_pixels,first_y_pixel,cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}
void Texture::showRocketLauncher(int frame_gun){
		//showWeapon(frame_gun,4,7,59);
		showWeapon(frame_gun,4);

		int first_x_pixel = 0;//Desde qué pixel en X quiero
		int cant_x_pixels = 490;
		int first_y_pixel = 0;
		int cant_y_pixels = 220;

		int windows_x_pos = width - 130;//Posicion inicial de X donde voy a mostrar el pixel
		int windows_y_pos = height + 15;//		
		int length_x = 120;
		int lenght_y = 80;
		genericShow(this->bar_guns[4],first_x_pixel,cant_x_pixels,first_y_pixel,cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}


void Texture::genericShow(SDL_Texture* texture, int first_x_pixel, int cant_x_pixels, int first_y_pixel, int cant_y_pixel,\
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

void Texture::showEnemy(SDL_Texture* texture, int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture){
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

	genericShow(texture,first_x_pixel,cant_x_pixels,first_y_pixel,cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}


void Texture::showGuard(int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture, bool is_shooting){
	showEnemy(this->enemies[0], state, frame, x_pixel, distance_player_plane, number_line_texture);
	if(is_shooting)
		showEnemy(this->shooting_effect[0],state,0,x_pixel,distance_player_plane, number_line_texture);
}

void Texture::showOfficer(int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture, bool is_shooting){
	showEnemy(this->enemies[1], state, frame, x_pixel, distance_player_plane, number_line_texture);
	if(is_shooting)
		showEnemy(this->shooting_effect[1],state,0,x_pixel,distance_player_plane, number_line_texture);
}

void Texture::showSs(int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture, bool is_shooting){
	showEnemy(this->enemies[2], state, frame, x_pixel, distance_player_plane, number_line_texture);
	if(is_shooting)
		showEnemy(this->shooting_effect[2],state,0,x_pixel,distance_player_plane, number_line_texture);
}

void Texture::showMutant(int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture, bool is_shooting){
	showEnemy(this->enemies[3], state, frame, x_pixel, distance_player_plane, number_line_texture);
	if(is_shooting)
		showEnemy(this->shooting_effect[3],state,0,x_pixel,distance_player_plane, number_line_texture);
}

void Texture::showDog(int state, int frame,int x_pixel, float distance_player_plane, int number_line_texture, bool is_shooting){
	showEnemy(this->enemies[4], state, frame, x_pixel, distance_player_plane, number_line_texture);
}

void Texture::showWall(SDL_Texture* texture,int x_pixel,float distance_player_plane, int number_line_texture){
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

	genericShow(texture,first_x_pixel,cant_x_pixels,first_y_pixel,cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}


void Texture::showWallGreystone(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::showWallBluestone(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*1 + wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::showWallPurplestone(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*2 + wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::showWallColorstone(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*3 + wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::showWallEagle(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*4 + wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::showWallMossy(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*5 + wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::showWallRedbrick(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*6 + wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::showWallWood(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	int current_texture = 2*7 + wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel, distance_player_plane, number_line_texture);
}

void Texture::showDoor(int x_pixel,float distance_player_plane, int number_line_texture, bool wall_side_y){
	showWall(door, x_pixel, distance_player_plane, number_line_texture);
}

static void sortValues(int &first_value, int &second_value){
	if(first_value>second_value){
		int temporal_value = first_value;
		first_value = second_value;
		second_value = temporal_value;
	}
}

void Texture::showSprite(int first_x_pixel,int first_number_line_texture,int last_x_pixel, int last_number_line_texture,float distance_player_plane,int texture){
	sortValues(first_x_pixel,last_x_pixel);
	sortValues(first_number_line_texture,last_number_line_texture);

	float lineHeight = (this->height / distance_player_plane);
	int initial_position_y =  -lineHeight/2 + height/2;
	float pixel_length = lineHeight/64;
	int x_initial_pos = x_lenght_ray*first_x_pixel;
	int height_ray = (int)ceil((pixel_length)*64);
	
	genericShow(this->sprites[texture],first_number_line_texture, last_number_line_texture - first_number_line_texture,0,64,\
		x_initial_pos,(int)x_lenght_ray*(last_x_pixel - first_x_pixel),initial_position_y,height_ray);
}

void Texture::showEndgame(){

	int first_x_pixel = 0;
	int cant_x_pixels = 662;
	int first_y_pixel = 0;
	int cant_y_pixels = 281;

	int windows_x_pos = 0;
	int windows_y_pos = 0;
	int length_x = width;
	int lenght_y = height;

	genericShow(endig_background,first_x_pixel,cant_x_pixels,first_y_pixel,cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);	
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
