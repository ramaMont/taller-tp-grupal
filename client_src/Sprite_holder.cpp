#include "Sprite_holder.h"

#include "Enemy.h"

Sprite_holder::Sprite_holder(Coordinates posicion, int texture, Player &player): 
Posicionable(posicion),Sprite_drawer(this,player) ,character(nullptr), colidable(false){
  	sprites_textures.push_back(texture);
}

void Sprite_holder::is_colidable(){
	this->colidable=true;
}

void Sprite_holder::add_sprite(int num_texture){
  	sprites_textures.push_back(num_texture);
}

void Sprite_holder::colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
    spotted();
    ray->sprite_colided(coordinates_map);
}    

void Sprite_holder::spotted(){
    spotted_sprite();
    if(character!=nullptr and player.get_position()!=posicion){
		Enemy* enemy = dynamic_cast<Enemy*>(character);
		enemy->spotted_sprite();
    }
}   

void Sprite_holder::add(Character* new_character){
	if(character!=nullptr or colidable){
		throw -2;
	}else{
		character=new_character;
	}

}

void Sprite_holder::remove(){
	character = nullptr;
}


void Sprite_holder::draw(const std::vector<float> &distances, int n_rays){
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
		texture_drawer->show_sprite(first_sigted_ray,first_num_pixel,last_sigted_ray,last_num_pixel,player_distance ,sprites_textures[j]);
	}

	if(character!=nullptr and player.get_position()!=posicion){
		Enemy* enemy = dynamic_cast<Enemy*>(character);
		enemy->draw(distances,n_rays);
	}
}
