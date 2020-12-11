#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <exception>
#include <algorithm>

#include "ray_casting.h"
#include "window.h"
#include "camera.h"

class Sprite;
#include <Sprite.h>
#include <Jugador.h>
#include <Mapa.h>

static void sort_vector(std::vector<Sprite*> &spotted_sprites){
	std::sort(spotted_sprites.begin(),
	          spotted_sprites.end(),
	          [](const Sprite* sprite, const Sprite* another_sprite)
	{
	    return sprite->get_distance_player_plane() > another_sprite->get_distance_player_plane();
	});	
}

// Fondo del juego: el piso y el techo
class Screen{

	private:

		int n_rays;
		std::vector<Sprite*> &sprites;
		Jugador &player;
		Mapa &map;
		Drawer drawer;
		Background background;
		Raycasting raycasting;


		void unsee_sprites(){
			for(unsigned int i=0; i<sprites.size(); i++){
				sprites[i]->disable_spotted();
			}
		}

		void get_spotted_sprites(std::vector<Sprite*> &spotted_sprites){
			for(unsigned int i=0; i<sprites.size(); i++){
				if(sprites[i]->is_spotted()){
					spotted_sprites.push_back(sprites[i]);
				}
			}
		}

		void initialice_spotted_sprites(std::vector<Sprite*> &spotted_sprites, Camera &camera){
			for(unsigned int j=0; j<spotted_sprites.size(); j++){
				for(int i=-2*n_rays; i<=2*n_rays; i++){
					Coordinates ray_direction = camera.calculate_ray_direction(i,n_rays);
					spotted_sprites[j]->update_distance_to_closest_ray(i,ray_direction);
				}
				spotted_sprites[j]->set_distance(camera.get_camera_plane());
			}

			sort_vector(spotted_sprites);
		}

	public:
		Screen(std::vector<Sprite*> &sprites, Jugador &player, Mapa &map, const Window &window):
		n_rays(160), sprites(sprites), player(player),
		map(map),
		drawer(window,n_rays,player),
		background(window), 
		raycasting(player, map, n_rays, drawer){}

		void show(){
			unsee_sprites();

			background.show();

			Camera camera(player.get_coordinates(),player.get_direction());

			std::vector<float> distances;
			raycasting.calculate_raycasting(camera,distances);

			std::vector<Sprite*> spotted_sprites;
			get_spotted_sprites(spotted_sprites);
			initialice_spotted_sprites(spotted_sprites,camera);

			for(unsigned int j=0; j<spotted_sprites.size(); j++){
				spotted_sprites[j]->draw(drawer,distances,n_rays);
			}

		}
};
#endif
