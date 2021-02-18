#include "SpriteHolder.h"

#include "Enemy.h"

SpriteHolder::SpriteHolder(Coordinates posicion, Player &player):
Posicionable(posicion),SpriteDrawer(this,player),
character(nullptr),has_explosion(false) ,explosion_frame(0) ,colidable(false){}

void SpriteHolder::isColidable(){
	this->colidable=true;
}

void SpriteHolder::addExplosion(){
	has_explosion = true;
	explosion_frame = 0;
}

void SpriteHolder::updateExplosion(){
	explosion_frame++;
	if(explosion_frame>23){
		has_explosion = false;
	}
}

bool SpriteHolder::explosionComplete(){
	return explosion_frame>23;
}

bool SpriteHolder::hasTextures(){
	return sprites_textures.size()>0;
}

void SpriteHolder::addSprite(int num_texture){
  	sprites_textures.push_back(num_texture);
}

void SpriteHolder::colisioned(Ray* ray,Coordinates coord_map,bool first_tri){
    spotted();
    ray->spriteColided(coord_map);
}    


/*Puedo realizar este casteo porque si estoy en este
 metodo, fui tocado por un rayo, por lo que no almaceno 
 al Jugador, y sí a un enemigo, o un misil*/
void SpriteHolder::spotted(){
    spottedSprite();
    if (character!=nullptr and player.get_position()!=posicion){
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

void SpriteHolder::callDrawer(int first_sigted_ray,int first_num_pixel,\
				int last_sigted_ray,int last_num_pixel,float player_distance){
	for(unsigned int j=0; j<sprites_textures.size(); j++){
		texture_drawer->showSprite(first_sigted_ray,first_num_pixel,
			last_sigted_ray,last_num_pixel,player_distance ,sprites_textures[j]);
	}

	if(has_explosion){
		texture_drawer->showExplosion(first_sigted_ray,first_num_pixel,
				last_sigted_ray,last_num_pixel,player_distance, (explosion_frame/3)%8);
	}
}
