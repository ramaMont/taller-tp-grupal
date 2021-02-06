#include "Screen.h"

static void sortVector(std::vector<SpriteDrawer*> &spotted_sprites){
	std::sort(spotted_sprites.begin(),
	          spotted_sprites.end(),
	          [](const SpriteDrawer* sprite, const SpriteDrawer* another_sprite)
	{
	    return sprite->getDistancePlayerPlane() > another_sprite->getDistancePlayerPlane();
	});	
}

Screen::Screen(std::vector<Enemy*> &enemies,std::vector<SpriteHolder*> &sprites, Player &player, ClMap &map,Texture &texture, Window &window):
	n_rays(window.getResolutionWidth()/2),enemies(enemies) ,sprites(sprites), player(player),
	map(map),
	texture(texture),
	window(window),
	background(window), 
	raycasting(player, map, n_rays){}


void Screen::unseeSprites(){
	for(unsigned int i=0; i<sprites.size(); i++){
		sprites[i]->disableSpotted();
	}
	
	for(unsigned int i=0; i<enemies.size(); i++){
		enemies[i]->disableSpotted();
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
}	

void Screen::initialiceSpottedSprites(std::vector<SpriteDrawer*> &spotted_sprites,Camera &camera){
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
	initialiceSpottedSprites(spotted_sprites,camera);
	for(unsigned int j=0; j<spotted_sprites.size(); j++){
		spotted_sprites[j]->draw(distances,n_rays);
	}

	player.draw();

	window.render();
}


void Screen::showEndgame(){
	window.setNoColor();
	texture.showEndgame();
	window.render();
}