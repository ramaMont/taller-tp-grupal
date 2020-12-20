#include "Sprite_holder.h"


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
	for(int i=0 ; i<cant_rays ; i++){
		int num_pixel = i*64/cant_rays;
		int current_ray = first_ray + i+ n_rays;
		if((current_ray)>0 and (current_ray)<2*n_rays){
			if(distances[current_ray]>player_distance){
				for(unsigned int j=0; j<sprites_textures.size(); j++){
					texture_drawer.show_sprite(first_ray + i,player_distance ,num_pixel,sprites_textures[j]);
				}
			}
		}
	}
}
