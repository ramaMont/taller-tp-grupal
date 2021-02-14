#include "texture.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>
#include <utility>

#include "SpriteValues.h"

static void sortValues(int &first_value, int &second_value){
	if(first_value>second_value){
		int temporal_value = first_value;
		first_value = second_value;
		second_value = temporal_value;
	}
}

void Texture::addWallTexture(std::string new_texture){
	std::string texture_store = "../data/textures/" + new_texture+".png";
    SDL_Surface* loadedSurface = IMG_Load(texture_store.c_str());
    wall_textures.push_back(SDL_CreateTextureFromSurface(renderer, 
    														loadedSurface));
	SDL_FreeSurface(loadedSurface);
	texture_store="../data/textures/" + new_texture+"_shaded.png";
    loadedSurface = IMG_Load(texture_store.c_str());
    wall_textures.push_back(SDL_CreateTextureFromSurface(renderer, 
    														loadedSurface));
	SDL_FreeSurface(loadedSurface);
}

void Texture::addSpriteTexture(std::string new_texture){
	std::string texture_store = "../data/textures/" + new_texture+".png";
    SDL_Surface* loadedSurface = IMG_Load(texture_store.c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 0, 0, 0);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
	int num_texture = texture_values.at(new_texture);
	sprites.insert(std::pair<int,SDL_Texture*>(num_texture,
							SDL_CreateTextureFromSurface(renderer, loadedSurface)));
	SDL_FreeSurface(loadedSurface);	
}

void Texture::addShootingEffectTexture(std::string new_texture){
	std::string texture_store = "../data/textures/" + new_texture+".png";
    SDL_Surface* loadedSurface = IMG_Load(texture_store.c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
    shooting_effect.push_back(SDL_CreateTextureFromSurface(renderer,
    													loadedSurface));
	SDL_FreeSurface(loadedSurface);		
}

void Texture::addEnemyTexture(std::string new_texture){
	std::string texture_store = "../data/textures/" + new_texture+".png";
    SDL_Surface* loadedSurface = IMG_Load(texture_store.c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
    enemies.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);		
}

void Texture::addDeadEnemyTexture(std::string new_texture){
	std::string texture_store = "../data/textures/dead_enemies/";
	texture_store += new_texture+".png";
    SDL_Surface* loadedSurface = IMG_Load(texture_store.c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
    sprites.insert(std::pair<int,SDL_Texture*>(texture_values.at(new_texture),
    					SDL_CreateTextureFromSurface(renderer, loadedSurface)));
	SDL_FreeSurface(loadedSurface);		
}

void Texture::addGunTexture(std::string new_texture){
	std::string texture_store = "../data/textures/" + new_texture+".png";
    SDL_Surface* loadedSurface = IMG_Load(texture_store.c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
	guns = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);		
}

void Texture::addDoorTextures(){
	std::string texture_store = "../data/textures/door.png";
    SDL_Surface* loadedSurface = IMG_Load(texture_store.c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
	door = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);			
}

void Texture::addKeyDoorTexture(){
	std::string texture_store = "../data/textures/key_door_client.png";
    SDL_Surface* loadedSurface = IMG_Load(texture_store.c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 152, 0, 136);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
	key_door = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);			
}

void Texture::addLifeBarTexture(std::string new_texture){
	std::string texture_store = "../data/textures/bar_textures/";
	texture_store += new_texture+".png";
    SDL_Surface* loadedSurface = IMG_Load(texture_store.c_str());
	life_bar = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);		
}

void Texture::addFaceHealth(){
	std::string texture_store = "../data/textures/bar_textures/face_health.png";
    SDL_Surface* loadedSurface = IMG_Load(texture_store.c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 255, 255, 255);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
	face_health = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);		
}

void Texture::addBarGuns(std::string new_texture){
	std::string texture_store = "../data/textures/bar_textures/";
	texture_store += new_texture+".png";
    SDL_Surface* loadedSurface = IMG_Load(texture_store.c_str());
    bar_guns.push_back(SDL_CreateTextureFromSurface(renderer, loadedSurface));
	SDL_FreeSurface(loadedSurface);		
}

void Texture::addKeyTexture(){
	std::string texture_store = "../data/textures/bar_textures/key.png";
    SDL_Surface* loadedSurface = IMG_Load(texture_store.c_str());
    key = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);	
}

void Texture::addEndingBackground(){
	std::string texture_store = "../data/ending_background.png";
    SDL_Surface* loadedSurface = IMG_Load(texture_store.c_str());
    Uint32 colorkey = SDL_MapRGB(loadedSurface->format, 255, 255, 255);
	SDL_SetColorKey(loadedSurface, SDL_TRUE, colorkey);	
	ending_background = SDL_CreateTextureFromSurface(renderer, loadedSurface);
	SDL_FreeSurface(loadedSurface);		
}

Texture::Texture(const Window& window):
	renderer(window.getRenderer()), info_bar_height(window.getInfoBarHeight()),
	height(window.getHeight()-info_bar_height),
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
		addKeyDoorTexture();

		addLifeBarTexture("life_bar");

		addBarGuns("knife");
		addBarGuns("gun");
		addBarGuns("machine_gun");
		addBarGuns("chain_gun");
		addBarGuns("rocket_launcher");

		addFaceHealth();
	    
	    addKeyTexture();

		addEndingBackground();
		if (TTF_Init() < 0) {
		    printf("error inicializacionnnn\n");
		}
		this->wolfensteinFont = TTF_OpenFont("../data/wolfenstein_font.ttf", 24);
		if(!wolfensteinFont){
			printf("Font no encontrada\n");
		}
}


void Texture::showFaceHealth(int portion_health){
	int first_x_pixel = 0;
	int cant_x_pixels = 145;
	int first_y_pixel = 0;
	int cant_y_pixels = 190;

	int windows_x_pos = width*0.42;
	int windows_y_pos = height + info_bar_height*0.1;
	int length_x = width/12;
	int lenght_y = info_bar_height*0.8;

	if(portion_health==1){
		first_x_pixel = 433;
		first_y_pixel = 190;
	}else if (portion_health==2){
		first_x_pixel = 289;
		first_y_pixel = 190;
	}else if (portion_health==3){
		first_x_pixel = 144;
		first_y_pixel = 190;
	}else if (portion_health==4){
		first_x_pixel = 0;
		first_y_pixel = 190;
	}else if (portion_health==5){
		first_x_pixel = 433;
		first_y_pixel = 0;
	}else if (portion_health==6){
		first_x_pixel = 289;
		first_y_pixel = 0;
	}else if (portion_health==7){
		first_x_pixel = 144;
		first_y_pixel = 0;
	}else{
		first_x_pixel = 0;
		first_y_pixel = 0;
	}
	genericShow(face_health,first_x_pixel,cant_x_pixels,first_y_pixel,
					cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}

void Texture::showKeys(bool has_key_1, bool has_key_2){
	int first_x_pixel = 0;//Desde qué pixel en X quiero
	int cant_x_pixels = 18;
	int first_y_pixel = 0;
	int cant_y_pixels = 30;

    if (has_key_1){
		int windows_x_pos = width*0.768;
		int windows_y_pos = height*1.02;
		int length_x = width*0.02;
		int lenght_y = height*0.09;

        genericShow(key,first_x_pixel,cant_x_pixels,first_y_pixel,
        			cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
    }
    if (has_key_2){
		int windows_x_pos = width*0.768;
		int windows_y_pos = height*1.14;
		int length_x = width*0.02;
		int lenght_y = height*0.09;
        
        genericShow(key,first_x_pixel,cant_x_pixels,first_y_pixel,
        			cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
    }
}

void Texture::showLifeBar(int id, unsigned int score, int lives,int health, \
				int portion_health, int ammo, bool has_key_1, bool has_key_2){
	    genericShow(life_bar,0,1097,0,127,0,width,height,info_bar_height);
	    //Ancho,alto,pos_x,pos_y
	    int distante_to_bar = height+info_bar_height*0.28;
	    std::string id_text = std::to_string(id).c_str();
	    std::string score_text = std::to_string(score).c_str();
	    std::string lives_text = std::to_string(lives).c_str();
	    std::string text_health = std::to_string(health).c_str();
	    std::string text_ammo = std::to_string(ammo).c_str();
		showText(white, id_text,width/16,
					distante_to_bar*0.2,width*0.1,distante_to_bar);
	    showText(white, score_text,width/16,
	    			distante_to_bar*0.2,width*0.3,distante_to_bar);
	    showText(white, lives_text,width/16,
	    			distante_to_bar*0.2,width*0.39,distante_to_bar);
	    int health_width = width*0.037;
	    if (strlen(text_health.c_str())>2){
	    	health_width = width*0.028;
		}
		showText(white, text_health,health_width,height/5,
					width*0.6,distante_to_bar);	    	    	
	    showText(white, text_ammo,width*0.035,height/5,
	    			width*0.75,distante_to_bar);	    

	    showFaceHealth(portion_health);
        
        showKeys(has_key_1, has_key_2);
}

void Texture::showText(Colors selected_color, std::string text, \
				int letter_width, int letter_height, int x_pos, int y_pos){
	SDL_Color color = { 62, 62, 62};  // Gris por defecto
	if(selected_color == black){
		color = {0, 0, 0};
	}else{ //Blanco
		color = {255, 255, 255};
	}

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(wolfensteinFont, 
														text.c_str(), color);

	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer,
														surfaceMessage);

	int len_message = letter_width*(int)strlen(text.c_str());

	const SDL_Rect sdlDst = {
	    x_pos - len_message, 
	    y_pos, 
	    len_message, 
	    letter_height
	};

	SDL_RenderCopy(renderer, message, NULL, &sdlDst);
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(message);	
}

void Texture::showWeapon(int frame_gun, int current_gun){
	int first_x_pixel = 129*frame_gun;
	int cant_x_pixels = 128;
	int first_y_pixel = current_gun*129;
	int cant_y_pixels = 128;

	int windows_x_pos = width*0.39;
	int windows_y_pos = height*0.595;//		
	int length_x = width*0.23;
	int lenght_y = height*0.41;

	genericShow(guns,first_x_pixel,cant_x_pixels,first_y_pixel,cant_y_pixels,
						windows_x_pos,length_x,windows_y_pos,lenght_y);
}

void Texture::showKnife(int frame_gun){
		//showWeapon(frame_gun,0,27,53);
		showWeapon(frame_gun,0);

		int first_x_pixel = 0;//Desde qué pixel en X quiero
		int cant_x_pixels = 450;
		int first_y_pixel = 0;
		int cant_y_pixels = 150;

		int windows_x_pos = width*0.8;
		int windows_y_pos = height*1.04;//		
		int length_x = width*0.19;
		int lenght_y = height*0.17;
		genericShow(this->bar_guns[0],first_x_pixel,cant_x_pixels,first_y_pixel,
						cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}
void Texture::showGun(int frame_gun){
		showWeapon(frame_gun,1);

		int first_x_pixel = 0;//Desde qué pixel en X quiero
		int cant_x_pixels = 400;
		int first_y_pixel = 0;
		int cant_y_pixels = 190;

		int windows_x_pos = width*0.8;
		int windows_y_pos = height*1.04;//		
		int length_x = width*0.19;
		int lenght_y = height*0.17;
		genericShow(this->bar_guns[1],first_x_pixel,cant_x_pixels,first_y_pixel,
						cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}
void Texture::showMachineGun(int frame_gun){
		//showWeapon(frame_gun,2,13,52);
		showWeapon(frame_gun,2);

		int first_x_pixel = 0;//Desde qué pixel en X quiero
		int cant_x_pixels = 460;
		int first_y_pixel = 0;
		int cant_y_pixels = 170;

	int windows_x_pos = width*0.8;
	int windows_y_pos = height*1.03;//		
	int length_x = width*0.19;
	int lenght_y = height*0.19;
		genericShow(this->bar_guns[2],first_x_pixel,cant_x_pixels,first_y_pixel,
						cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}
void Texture::showChainGun(int frame_gun){
		//showWeapon(frame_gun,3,7,59);
		showWeapon(frame_gun,3);

		int first_x_pixel = 0;//Desde qué pixel en X quiero
		int cant_x_pixels = 490;
		int first_y_pixel = 0;
		int cant_y_pixels = 220;

		int windows_x_pos = width*0.8;
		int windows_y_pos = height*1.03;//		
		int length_x = width*0.19;
		int lenght_y = height*0.19;
		genericShow(this->bar_guns[3],first_x_pixel,cant_x_pixels,first_y_pixel,
						cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}
void Texture::showRocketLauncher(int frame_gun){
		//showWeapon(frame_gun,4,7,59);
		showWeapon(frame_gun,4);

		int first_x_pixel = 0;//Desde qué pixel en X quiero
		int cant_x_pixels = 490;
		int first_y_pixel = 0;
		int cant_y_pixels = 220;

		int windows_x_pos = width*0.8;
		int windows_y_pos = height*1.02;//		
		int length_x = width*0.19;
		int lenght_y = height*0.21;
		genericShow(this->bar_guns[4],first_x_pixel,cant_x_pixels,first_y_pixel,
						cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}


void Texture::genericShow(SDL_Texture* texture, int first_x_pixel, \
					int cant_x_pixels, int first_y_pixel, int cant_y_pixel,\
					int windows_x_pos, int length_x, int windows_y_pos, int length_y){
		showableTexture.x = first_x_pixel; //Desde qué textura en X quiero
		showableTexture.w = cant_x_pixels; //Cantidad de textura en X que tomo
		showableTexture.y = first_y_pixel;	//Desde qué textura en Y quiero
		showableTexture.h = cant_y_pixel; //Cantidad de textura en Y que tomo
	     const SDL_Rect sdlDst = {
	        windows_x_pos, //Posicion inicial de X donde voy a mostrar el pixel
	        windows_y_pos, //Posicion inicial de Y donde voy a mostrar el pixel
	        length_x, //Ancho en pixeles de X donde voy a mostrar lo pedido
	        length_y//Alto en pixeles de Y donde voy a mostrar lo pedido
	    };     
	    SDL_RenderCopy(this->renderer, texture, &showableTexture, &sdlDst);
}

void Texture::showEnemy(int num_enemy,int first_x_pixel, \
				int first_number_line_texture,int last_x_pixel, \
				int last_number_line_texture,float distance_player_plane,\
							int frame, int state, bool shooting){
	sortValues(first_x_pixel,last_x_pixel);
	sortValues(first_number_line_texture,last_number_line_texture);


	float lineHeight = (this->height / distance_player_plane);
	int initial_position_y =  -lineHeight/2 + height/2;
	float pixel_length = lineHeight/64;
	int x_initial_pos = first_x_pixel;
	int height_ray = (int)ceil((pixel_length)*64);


	int first_x_pixel_ = 65*frame + first_number_line_texture;
	int cant_x_pixels_ = last_number_line_texture - first_number_line_texture;
	int first_y_pixel_ = state*65;
	int cant_y_pixels_ = 64;

	int x_width = last_x_pixel - first_x_pixel;
	genericShow(this->enemies[num_enemy],first_x_pixel_,
				 	cant_x_pixels_,first_y_pixel_,cant_y_pixels_,\
					x_initial_pos,x_width,initial_position_y,height_ray);

	if(shooting)
		genericShow(this->shooting_effect[num_enemy],first_x_pixel_,
					cant_x_pixels_,first_y_pixel_,cant_y_pixels_,\
					x_initial_pos,x_width,initial_position_y,height_ray);
}


void Texture::showGuard(int first_x_pixel,int first_number_line_texture,\
							int last_x_pixel, int last_number_line_texture,\
							float distance_player_plane,int frame, int state, bool shooting){
	showEnemy(0,first_x_pixel,first_number_line_texture,last_x_pixel,
					last_number_line_texture,distance_player_plane,frame,state,shooting);
}

void Texture::showOfficer(int first_x_pixel,int first_number_line_texture,\
							int last_x_pixel, int last_number_line_texture,\
							float distance_player_plane,int frame, int state, bool shooting){
	showEnemy(1,first_x_pixel,first_number_line_texture,last_x_pixel,
					last_number_line_texture,distance_player_plane,frame,state,shooting);
}

void Texture::showSs(int first_x_pixel,int first_number_line_texture,\
							int last_x_pixel, int last_number_line_texture,\
							float distance_player_plane,int frame, int state, bool shooting){
	showEnemy(2,first_x_pixel,first_number_line_texture,last_x_pixel,
					last_number_line_texture,distance_player_plane,frame,state,shooting);
}

void Texture::showMutant(int first_x_pixel,int first_number_line_texture,\
							int last_x_pixel, int last_number_line_texture,\
							float distance_player_plane,int frame, int state, bool shooting){
	showEnemy(3,first_x_pixel,first_number_line_texture,last_x_pixel,
					last_number_line_texture,distance_player_plane,frame,state,shooting);
}


void Texture::showDog(int first_x_pixel,int first_number_line_texture,\
							int last_x_pixel, int last_number_line_texture,\
							float distance_player_plane,int frame, int state, bool shooting){
	showEnemy(4,first_x_pixel,first_number_line_texture,last_x_pixel,
					last_number_line_texture,distance_player_plane,frame,state,false);
}

void Texture::showWall(SDL_Texture* texture,int x_pixel, \
					float distance_player_plane, int number_line_texture){
	float lineHeight = (this->height / distance_player_plane);
	int initial_position_y =  -lineHeight/2 + height/2;

	float pixel_length = lineHeight/64;

	int height_ray = (int)ceil(pixel_length*64);	

	int first_x_pixel = number_line_texture;
	int cant_x_pixels = 1;
	int first_y_pixel = 0;
	int cant_y_pixels = 64;

	int windows_x_pos = x_pixel;
	int windows_y_pos = initial_position_y;
	int length_x = 1;
	int lenght_y = height_ray;

	genericShow(texture,first_x_pixel,cant_x_pixels,first_y_pixel,
				cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);
}


void Texture::showWallGreystone(int x_pixel,float distance_player_plane, \
						int number_line_texture, bool wall_side_y){
	int current_texture = wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel, 
						distance_player_plane, number_line_texture);
}

void Texture::showWallBluestone(int x_pixel,float distance_player_plane, \
						int number_line_texture, bool wall_side_y){
	int current_texture = 2*1 + wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel, 
						distance_player_plane, number_line_texture);
}

void Texture::showWallPurplestone(int x_pixel,float distance_player_plane, \
						int number_line_texture, bool wall_side_y){
	int current_texture = 2*2 + wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel, 
						distance_player_plane, number_line_texture);
}

void Texture::showWallColorstone(int x_pixel,float distance_player_plane, \
						int number_line_texture, bool wall_side_y){
	int current_texture = 2*3 + wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel, 
						distance_player_plane, number_line_texture);
}

void Texture::showWallEagle(int x_pixel,float distance_player_plane, \
						int number_line_texture, bool wall_side_y){
	int current_texture = 2*4 + wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel, 
						distance_player_plane, number_line_texture);
}

void Texture::showWallMossy(int x_pixel,float distance_player_plane, \
						int number_line_texture, bool wall_side_y){
	int current_texture = 2*5 + wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel, 
						distance_player_plane, number_line_texture);
}

void Texture::showWallRedbrick(int x_pixel,float distance_player_plane, \
						int number_line_texture, bool wall_side_y){
	int current_texture = 2*6 + wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel, 
						distance_player_plane, number_line_texture);
}

void Texture::showWallWood(int x_pixel,float distance_player_plane, \
						int number_line_texture, bool wall_side_y){
	int current_texture = 2*7 + wall_side_y;
	showWall(this->wall_textures[current_texture], x_pixel,
						distance_player_plane, number_line_texture);
}

void Texture::showDoor(int x_pixel,float distance_player_plane,\
						 int number_line_texture, bool wall_side_y){
	showWall(door, x_pixel, distance_player_plane, number_line_texture);
}

void Texture::showKeyDoor(int x_pixel,float distance_player_plane,\
						 int number_line_texture, bool wall_side_y){
	showWall(key_door, x_pixel, distance_player_plane, number_line_texture);
}

void Texture::showSprite(int first_x_pixel,int first_number_line_texture, \
				int last_x_pixel, int last_number_line_texture, \
				float distance_player_plane,int texture){
	sortValues(first_x_pixel,last_x_pixel);
	sortValues(first_number_line_texture,last_number_line_texture);

	float lineHeight = (this->height / distance_player_plane);
	int initial_position_y =  -lineHeight/2 + height/2;
	float pixel_length = lineHeight/64;
	int x_initial_pos = first_x_pixel;
	int height_ray = (int)ceil((pixel_length)*64);
	
	int length_texture = last_number_line_texture - first_number_line_texture;
	int cant_pixels = last_x_pixel - first_x_pixel;
	genericShow(this->sprites[texture],first_number_line_texture, 
		length_texture,0,64, x_initial_pos,cant_pixels,
		initial_position_y,height_ray);
}
void Texture::showRanking(
				std::vector<std::pair<int,int>> &ordered_players_kills, \
    			std::vector<std::pair<int,int>> &ordered_players_points, \
    			std::vector<std::pair<int,int>> &ordered_players_bullets){
    int distante_to_bar = height+info_bar_height*0.28;
    int position = 0;
    for (auto& player : ordered_players_kills){
    	std::string player_kills = std::to_string(player.first).c_str();
    	std::string player_id = std::to_string(player.second).c_str();
		showText(black, player_kills,width/16,distante_to_bar*0.17,
								width*0.13, height*0.39 + position*height*0.14);
	    showText(black, player_id,width/16,distante_to_bar*0.17,
	    						width*0.23, height*0.39 + position*height*0.14);
        ++position;
    }
    position = 0;
    for (auto& player : ordered_players_points){
    	int points = player.first;
    	std::string player_points = std::to_string(player.first).c_str();
    	std::string player_id = std::to_string(player.second).c_str();
    	int x_pos = width/16;
    	if(points>=100){ //Tiene 3 digitos
    		x_pos = width*3/64;
    	}
    	showText(black, player_id,width/16,distante_to_bar*0.17,
    						width*0.45, height*0.39 + position*height*0.14);
	    showText(black, player_points,x_pos,distante_to_bar*0.17,
	    					width*0.60, height*0.39 + position*height*0.14);
        ++position;
    }
    position = 0;
    for (auto& player : ordered_players_bullets){
    	int bullets = player.first;
    	std::string player_bullets = std::to_string(player.first);
    	std::string player_id = std::to_string(player.second);
		int x_pos = width/64;
    	if(bullets>=100){ //Tiene 3 digitos    	
    		x_pos = width*3/64;
    	}
		showText(black, player_id,width/16,distante_to_bar*0.17,
						width*0.80, height*0.39 + position*height*0.14);
		showText(black, player_bullets,x_pos,distante_to_bar*0.17,
						width*0.97, height*0.39 + position*height*0.14);
        ++position;
    }
}

void Texture::showWinningScreen(
			std::vector<std::pair<int,int>> &ordered_players_kills, \
		    std::vector<std::pair<int,int>> &ordered_players_points, \
		    std::vector<std::pair<int,int>> &ordered_players_bullets){
	int first_x_pixel = 0;
	int cant_x_pixels = 913;
	int first_y_pixel = 0;
	int cant_y_pixels = 598;

	int windows_x_pos = 0;
	int windows_y_pos = 0;
	int length_x = width;
	int lenght_y = height + info_bar_height;

	genericShow(ending_background,first_x_pixel,cant_x_pixels,first_y_pixel,
					cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);	

	showText(black, "You won!!",width*3/64,height/8, width*0.735, height/10);

	showRanking(ordered_players_kills,
		ordered_players_points,ordered_players_bullets);
}

void Texture::showLoosingScreen(int winner_id,\
		std::vector<std::pair<int,int>> &ordered_players_kills, \
    	std::vector<std::pair<int,int>> &ordered_players_points, \
    	std::vector<std::pair<int,int>> &ordered_players_bullets){
	int first_x_pixel = 0;
	int cant_x_pixels = 913;
	int first_y_pixel = 0;
	int cant_y_pixels = 598;

	int windows_x_pos = 0;
	int windows_y_pos = 0;
	int length_x = width;
	int lenght_y = height + info_bar_height;

	genericShow(ending_background,first_x_pixel,cant_x_pixels,first_y_pixel,
				cant_y_pixels,windows_x_pos,length_x,windows_y_pos,lenght_y);

	std::string id_text = std::to_string((int16_t)winner_id);
	std::string winner_letter= "Winner id: " + id_text;

	showText(black, winner_letter,width*2/64,
						height/8, width*0.72, height/10);

	showRanking(ordered_players_kills,ordered_players_points,
											ordered_players_bullets);
}

void Texture::showDisconnectedScreen(){
	std::string message =  "Interrupted match";
	showText(white, message,width/32,height/8, width*7/10, height/2);	
}

void Texture::destoyVectorTextures(std::vector<SDL_Texture*> &texture_vector){
	for(auto& texture : texture_vector){
		SDL_DestroyTexture(texture);
	}
}

Texture::~Texture() {
	destoyVectorTextures(wall_textures);
	destoyVectorTextures(enemies);
	destoyVectorTextures(shooting_effect);
	destoyVectorTextures(bar_guns);

	int cant_textures = sprites.size();
	for(int i=0; i<cant_textures; i++){
		SDL_DestroyTexture(sprites[i]);
	}

	SDL_DestroyTexture(face_health);
	SDL_DestroyTexture(guns);
	SDL_DestroyTexture(door);
	SDL_DestroyTexture(key_door);
	SDL_DestroyTexture(life_bar);
	SDL_DestroyTexture(key);
	SDL_DestroyTexture(ending_background);

	TTF_CloseFont(wolfensteinFont);
}
