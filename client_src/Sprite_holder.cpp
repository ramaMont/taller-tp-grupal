#include "Sprite_holder.h"

#include "Enemy.h"

Sprite_holder::Sprite_holder(Coordinates posicion, int texture, Jugador &player): 
Posicionable(posicion),Sprite_drawer(this,player) ,movable(nullptr){
  	sprites_textures.push_back(texture);
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
    if(movable!=nullptr and player.get_position()!=posicion){
		Enemy* enemy = dynamic_cast<Enemy*>(movable);
		enemy->spotted_sprite();
    }
}   

void Sprite_holder::add(Movable* new_movable){
	if(movable!=nullptr){
		throw -2;
	}else{
		movable=new_movable;
	}

}

void Sprite_holder::remove(){
	movable = nullptr;
}


void Sprite_holder::draw(const std::vector<float> &distances, int n_rays){
	int first_ray = center_ray - cant_rays/2;
	bool first_ray_already_sigted = false;
	int first_sigted_ray = 0;
	int first_num_pixel = 0;
	int last_sigted_ray = 0;
	int last_num_pixel = 0;
	for(int i=0 ; i<cant_rays ; i++){
		int num_pixel = i*64/cant_rays;
		int current_ray = first_ray + i+ n_rays;
		if((current_ray)>0 and (current_ray)<2*n_rays){
			if(distances[current_ray]>player_distance){
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

	for(unsigned int j=0; j<sprites_textures.size(); j++){
		texture_drawer->show_sprite(first_sigted_ray,first_num_pixel,last_sigted_ray,last_num_pixel,player_distance ,sprites_textures[j]);
	}

	if(movable!=nullptr and player.get_position()!=posicion){
		Enemy* enemy = dynamic_cast<Enemy*>(movable);
		enemy->draw(distances,n_rays);
	}
}
