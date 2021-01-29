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
#include <Player.h>
#include <ClMap.h>


// Administra la visualizacion de todos los objetos visibles: sprites, enemigos, paredes y armas
class Screen{

	private:

		int n_rays;
		std::vector<Enemy*> &enemies;
		std::vector<Sprite_drawer*> &sprites;
		Player &player;
		ClMap &map;
		Texture &texture;
		Window &window;
		Background background;
		Raycasting raycasting;


		// Desactiva los sprites vistos en el frame anterior
		void unsee_sprites();

		// Obtiene los sprites(enemigos incluidos) vistos en el frame actual
		void get_spotted_sprites(std::vector<Sprite_drawer*> &spotted_sprites);

		// Realiza los calculos necesarios para la correcta visualizacion de los sprites: distancia al jugador, etc
		void initialice_spotted_sprites(std::vector<Sprite_drawer*> &spotted_sprites,Camera &camera);
	public:
		Screen(std::vector<Enemy*> &enemies,std::vector<Sprite_drawer*> &sprites, Player &player, ClMap &map,Texture &texture, Window &window);

		// Llama a los metodos correspondientes para la correcta visualizacion
		void show();
};
#endif
