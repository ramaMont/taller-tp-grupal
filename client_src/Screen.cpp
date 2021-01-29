#include "Screen.h"

static void sort_vector(std::vector<Sprite_drawer*> &spotted_sprites){
	std::sort(spotted_sprites.begin(),
	          spotted_sprites.end(),
	          [](const Sprite_drawer* sprite, const Sprite_drawer* another_sprite)
	{
	    return sprite->get_distance_player_plane() > another_sprite->get_distance_player_plane();
	});	
}

Screen::Screen(std::vector<Enemy*> &enemies,std::vector<Sprite_drawer*> &sprites, Jugador &player, ClMap &map,Texture &texture, Window &window):
	n_rays(window.get_resolution_width()/2),enemies(enemies) ,sprites(sprites), player(player),
	map(map),
	texture(texture),
	window(window),
	background(window), 
	raycasting(player, map, n_rays){}


void Screen::unsee_sprites(){
	for(unsigned int i=0; i<sprites.size(); i++){
		sprites[i]->disable_spotted();
	}
}

void Screen::get_spotted_sprites(std::vector<Sprite_drawer*> &spotted_sprites){
	for(unsigned int i=0; i<sprites.size(); i++){
		if(sprites[i]->is_spotted()){
			spotted_sprites.push_back(sprites[i]);
		}
	}
}	

void Screen::initialice_spotted_sprites(std::vector<Sprite_drawer*> &spotted_sprites,Camera &camera){
	for(unsigned int j=0; j<spotted_sprites.size(); j++){
		spotted_sprites[j]->set_relative_angle_to_player();
		for(int i=-2*n_rays; i<=2*n_rays; i++){
			spotted_sprites[j]->update_distance_to_closest_ray(i,n_rays);
		}
		spotted_sprites[j]->set_distance(n_rays,camera.get_camera_plane());
	}
	sort_vector(spotted_sprites);
}


void Screen::show(){

	window.set_no_color();

	unsee_sprites();
	background.show();
	Camera camera(player.get_position(),player.get_direction());
	std::vector<float> distances;
	raycasting.calculate_raycasting(camera,distances);
	std::vector<Sprite_drawer*> spotted_sprites;
	get_spotted_sprites(spotted_sprites);
	initialice_spotted_sprites(spotted_sprites,camera);
	for(unsigned int j=0; j<spotted_sprites.size(); j++){
		spotted_sprites[j]->draw(distances,n_rays);
	}

	player.draw();

	window.render();
}
