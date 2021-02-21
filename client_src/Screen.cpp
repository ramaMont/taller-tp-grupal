#include "Screen.h"

#include <vector>
#include <algorithm>
#include <utility> 

static void sortVector(std::vector<SpriteDrawer*> &spotted_sprites){
	std::sort(spotted_sprites.begin(),
	          spotted_sprites.end(),
	          [](const SpriteDrawer* sprite, const SpriteDrawer* another_sprite)
	{
		float my_sprite_distance = sprite->getDistancePlayerPlane();
		float other_sprite_distance = another_sprite->getDistancePlayerPlane();
	    return my_sprite_distance > other_sprite_distance;
	});	
}

Screen::Screen(std::vector<Rocket*> &rockets,std::vector<Enemy*> &enemies, \
	std::vector<SpriteHolder*> &sprites, Player &player, ClientMap &map, \
										Texture &texture, Window &window):
	n_rays(window.getWidth()/2), rockets(rockets), 
	enemies(enemies) ,sprites(sprites), player(player),
	map(map), texture(texture), window(window), background(window), 
	raycasting(player, map, n_rays){}


void Screen::unseeSprites(){
	for(unsigned int i=0; i<sprites.size(); i++){
		sprites[i]->disableSpotted();
	}
	
	for(unsigned int i=0; i<enemies.size(); i++){
		enemies[i]->disableSpotted();
	}

	for(unsigned int i=0; i<rockets.size(); i++){
		rockets[i]->disableSpotted();
	}
}

void Screen::getSpottedSprites(std::vector<SpriteDrawer*> &spotted_sprites){
	for(unsigned int i=0; i<sprites.size(); i++){
		if(sprites[i]->isSpotted()){
			spotted_sprites.push_back(sprites[i]);
		}
	}
	for(unsigned int i=0; i<enemies.size(); i++){
		if(enemies[i]->isSpotted()){
			spotted_sprites.push_back(enemies[i]);
		}
	}
	for(unsigned int i=0; i<rockets.size(); i++){
		if(rockets[i]->isSpotted()){
			spotted_sprites.push_back(rockets[i]);
		}
	}
}	

void Screen::initialiceSpottedSprites(Camera &camera, \
		std::vector<SpriteDrawer*> &spotted_sprites){
	for(unsigned int j=0; j<spotted_sprites.size(); j++){
		spotted_sprites[j]->setRelativeAngleToPlayer();
		for(int i=-2*n_rays; i<=2*n_rays; i++){
			spotted_sprites[j]->updateDistanceToClosestRay(i,n_rays);
		}
		spotted_sprites[j]->setDistance(n_rays,camera.getCameraPlane());
	}
	sortVector(spotted_sprites);
}

void Screen::show(){
	window.setNoColor();
	unseeSprites();
	background.show();
	Camera camera(player.get_position(),player.getDirection());
	std::vector<float> distances;
	raycasting.calculateRayCasting(camera,distances);
	std::vector<SpriteDrawer*> spotted_sprites;
	getSpottedSprites(spotted_sprites);
	initialiceSpottedSprites(camera,spotted_sprites);
	for(unsigned int j=0; j<spotted_sprites.size(); j++){
		spotted_sprites[j]->draw(distances,n_rays);
	}
	player.draw();
	window.render();
}

void Screen::showEndgame(bool player_won, int winner_id, \
	bool game_done, bool game_canceled, \
	std::vector<std::pair<int,int>> &ordered_players_kills, \
	std::vector<std::pair<int,int>> &ordered_players_points, \
	std::vector<std::pair<int,int>> &ordered_players_bullets,\
	bool have_winner){

	if(game_canceled){
		window.setColor(62, 62, 62,0xFF);
		texture.showDisconnectedScreen();
	}else{
		if(player_won){
			window.setColor(0x0e,0x6b,0x0e,0xFF);
			texture.showWinningScreen(ordered_players_kills,
				ordered_players_points,ordered_players_bullets);
		}else if (have_winner){
			window.setColor(0x54,0x1e,0x1b,0xFF);
			texture.showLoosingScreen(winner_id,ordered_players_kills,
				ordered_players_points,ordered_players_bullets);
		} else {
			// aca mandarle que no hubo ganador
			window.setColor(0x54,0x1e,0x1b,0xFF);
			texture.showLoosingScreen(winner_id,ordered_players_kills,
				ordered_players_points,ordered_players_bullets);
		}
	}
	window.render();
}
