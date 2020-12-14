#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <exception>
#include <algorithm>

#include "ray_casting.h"
#include "window.h"
#include "camera.h"

class Sprite_drawer;
#include <Sprite_drawer.h>
class Enemy;
#include <Enemy.h>
#include <Jugador.h>
#include <Mapa.h>

static void sort_vector(std::vector<Sprite_drawer*> &spotted_sprites){
	std::sort(spotted_sprites.begin(),
	          spotted_sprites.end(),
	          [](const Sprite_drawer* sprite, const Sprite_drawer* another_sprite)
	{
	    return sprite->get_distance_player_plane() > another_sprite->get_distance_player_plane();
	});	
}

// Fondo del juego: el piso y el techo
class Screen{

	private:

		int n_rays;
		std::vector<Enemy*> &enemies;
		std::vector<Sprite_drawer*> &sprites;
		Jugador &player;
		Mapa &map;
		Drawer drawer;
		Background background;
		Raycasting raycasting;


		void unsee_sprites(){
			for(unsigned int i=0; i<sprites.size(); i++){
				sprites[i]->disable_spotted();
			}

			for(unsigned int i=0; i<enemies.size(); i++){
				enemies[i]->disable_spotted();
			}
		}

		void get_spotted_sprites(std::vector<Sprite_drawer*> &spotted_sprites){
			for(unsigned int i=0; i<sprites.size(); i++){
				if(sprites[i]->is_spotted()){
					spotted_sprites.push_back(sprites[i]);
				}
			}
		}

		void get_spotted_enemies(std::vector<Enemy*> &spotted_enemies){
			for(unsigned int i=0; i<enemies.size(); i++){
				if(enemies[i]->is_spotted()){
					spotted_enemies.push_back(enemies[i]);
				}
			}
		}		

		void initialice_spotted_sprites(std::vector<Sprite_drawer*> &spotted_sprites,Camera &camera){
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
		Screen(std::vector<Enemy*> &enemies,std::vector<Sprite_drawer*> &sprites, Jugador &player, Mapa &map, const Window &window):
		n_rays(160),enemies(enemies) ,sprites(sprites), player(player),
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
			std::vector<Sprite_drawer*> spotted_sprites;
			get_spotted_sprites(spotted_sprites);
			initialice_spotted_sprites(spotted_sprites,camera);
			for(unsigned int j=0; j<spotted_sprites.size(); j++){
				spotted_sprites[j]->draw(drawer,distances,n_rays);
			}

		}
};
#endif
