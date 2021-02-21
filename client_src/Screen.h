#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <exception>
#include <algorithm>

#include "window.h"
#include "camera.h"
class SpriteHolder;
#include "SpriteHolder.h"
class Rocket;
#include "Rocket.h"
class Enemy;
#include "Enemy.h"
#include "Player.h"
#include "ClientMap.h"

#include <utility>
#include <vector> 

/* Administra la visualizacion de todos los objetos
 visibles: raycasting y sprites(enemigos, paredes, armas)*/
class Screen{
	private:
		int n_rays;
		std::vector<Rocket*> &rockets;
		std::vector<Enemy*> &enemies;
		std::vector<SpriteHolder*> &sprites;
		Player &player;
		ClientMap &map;
		Texture &texture;
		Window &window;
		Background background;
		Raycasting raycasting;


		// Desactiva los sprites vistos en el frame anterior
		void unseeSprites();

		// Obtiene los sprites(enemigos incluidos) vistos en el frame actual
		void getSpottedSprites(std::vector<SpriteDrawer*> &spotted_sprites);

		/* Realiza los calculos necesarios para la correcta 
		visualizacion de los sprites: distancia al jugador, etc*/
		void initialiceSpottedSprites(Camera &camera,\
					 std::vector<SpriteDrawer*> &spotted_sprites);

	public:
		Screen(std::vector<Rocket*> &rockets, std::vector<Enemy*> &enemies, \
				std::vector<SpriteHolder*> &sprites, Player &player,\
				 ClientMap &map,Texture &texture, Window &window);

    	Screen(const Screen&) = delete;
    	Screen(Screen&& other) = delete;
    	Screen& operator=(const Screen&) = delete;
    	Screen& operator=(Screen&& other);

		// Llama a los metodos correspondientes para la correcta visualizacion
		void show();

		void showEndgame(bool player_won, int winnder_id,\
			bool game_done, bool game_canceled,\
			std::vector<std::pair<int,int>> &ordered_players_kills,\
			std::vector<std::pair<int,int>> &ordered_players_points,\
			std::vector<std::pair<int,int>> &ordered_players_bullets,
			bool have_winner);
};
#endif
