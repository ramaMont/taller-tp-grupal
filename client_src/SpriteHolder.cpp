#include "SpriteHolder.h"

#include "Enemy.h"

SpriteHolder::SpriteHolder(Coordinates posicion, int texture, Player &player): 
Posicionable(posicion),SpriteDrawer(this,player) ,character(nullptr), colidable(false){
  	sprites_textures.push_back(texture);
}

void SpriteHolder::isColidable(){
	this->colidable=true;
}

void SpriteHolder::addSprite(int num_texture){
  	sprites_textures.push_back(num_texture);
}

void SpriteHolder::colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
    spotted();
    ray->spriteColided(coordinates_map);
}    


/*Puedo realizar este casteo porque si estoy en este
 metodo, fui tocado por un rayo, por lo que no almaceno 
 al Jugador, y sí a un enemigo, o un misil*/
void SpriteHolder::spotted(){
    spottedSprite();
    if(character!=nullptr and player.get_position()!=posicion){
		SpriteDrawer* movable = dynamic_cast<SpriteDrawer*>(character);
		movable->spottedSprite();
    }
}   

void SpriteHolder::add(Movable* new_character){
	if(character!=nullptr or colidable){
		throw -2;
	}else{
		character=new_character;
	}

}

void SpriteHolder::remove(){
	character = nullptr;
}


bool SpriteHolder::hasCharacter(){
	return (character!=nullptr);
}

Movable* SpriteHolder::getCharacter(){
	return character;
}

/*void SpriteHolder::draw(const std::vector<float> &distances, int n_rays){
	int first_ray = center_ray - cant_rays/2;
	bool first_ray_already_sigted = false;
	int first_sigted_ray = 0;
	int first_num_pixel = 0;
	int last_sigted_ray = 0;
	int last_num_pixel = 0;

	int cant_spotted_rays = 0;
	for(int i=0 ; i<cant_rays ; i++){
		int num_pixel = i*64/cant_rays;
		int current_ray = first_ray + i+ n_rays;
		if((current_ray)>0 and (current_ray)<2*n_rays){
			if(distances[current_ray]>player_distance){
				cant_spotted_rays++;

				if(first_ray_already_sigted){
					last_sigted_ray = first_ray + i + n_rays;
					last_num_pixel = num_pixel;
				}
				else{
					first_sigted_ray = first_ray + i + n_rays;
					first_num_pixel = num_pixel;
				}

				first_ray_already_sigted = true;
			}
		}
	}

	if(cant_spotted_rays==1){
		last_sigted_ray = first_sigted_ray;
		last_num_pixel = first_num_pixel;
	}

	for(unsigned int j=0; j<sprites_textures.size(); j++){
		texture_drawer->showSprite(first_sigted_ray,first_num_pixel,last_sigted_ray,last_num_pixel,player_distance ,sprites_textures[j]);
	}

	if(character!=nullptr and player.get_position()!=posicion){
		character->draw(distances,n_rays);
	}
}*/

void SpriteHolder::callDrawer(int first_sigted_ray,int first_num_pixel,int last_sigted_ray,int last_num_pixel,float player_distance){
	for(unsigned int j=0; j<sprites_textures.size(); j++){
		texture_drawer->showSprite(first_sigted_ray,first_num_pixel,last_sigted_ray,last_num_pixel,player_distance ,sprites_textures[j]);
	}
}
