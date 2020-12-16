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


void Sprite_holder::draw(Drawer &drawer, const std::vector<float> &distances, int n_rays){
	int first_ray = center_ray - cant_rays/2;
	for(int i=0 ; i<cant_rays ; i++){
		int num_pixel = i*64/cant_rays;
		if((first_ray + i+ n_rays)>0 and (first_ray + i+ n_rays)<2*n_rays){
			if(distances[first_ray + i+ n_rays]>player_distance){
				for(unsigned int j=0; j<sprites_textures.size(); j++){
					drawer.draw_sprites(first_ray + i,player_distance ,num_pixel,sprites_textures[j]);
				}
			}
		}
	}
}
