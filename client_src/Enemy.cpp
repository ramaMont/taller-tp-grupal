#include "Enemy.h"

#include <math.h>

static int get_num_texture(Coordinates enemy_position, Coordinates enemy_direction, Coordinates player_position){
	Coordinates relative_player_pos;
	relative_player_pos.x = player_position.x - enemy_position.x;
	relative_player_pos.y = player_position.y - enemy_position.y;


	float dist = enemy_direction.x*relative_player_pos.x + enemy_direction.y*relative_player_pos.y;
	float det = enemy_direction.x*relative_player_pos.y - enemy_direction.y*relative_player_pos.x;

	float angle = atan2(det, dist);
	float abs_angle = std::abs(angle);
	int side = 0;
	if(abs_angle<M_PI/8)
		side = 0;
	else if(abs_angle<3*M_PI/8){
		if(angle<0)
			side = 7;
		else
			side = 1;
	}
	else if(abs_angle<5*M_PI/8){
		if(angle<0)
			side = 6;
		else
			side = 2;
	}
	else if(abs_angle<7*M_PI/8){
		if(angle<0)
			side = 5;
		else
			side = 3;
	}
	else
		side = 4;
	return side;
}


Enemy::Enemy(Coordinates posicion, Coordinates direction ,ClMap& map, Player &player ,int id):
    Character(posicion,direction,map,id),SpriteDrawer(this,player),
   	player(player), is_moving(false),
    moved_frames_continued(0), enemy_type(nullptr){
	   this->initial_position = posicion;
	   this->initial_direction = direction;    	
    }


void Enemy::colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
    spottedSprite();
    ray->spriteColided(coordinates_map);
} 

void Enemy::newEnemyType(int new_enemy_type){
  	if(enemy_type!=nullptr)
   		delete enemy_type;
   	if(new_enemy_type==0)
   		enemy_type = new Dog(texture_drawer);
   	else if(new_enemy_type==1)
   		enemy_type = new Guard(texture_drawer);
   	else if(new_enemy_type==2)
   		enemy_type = new SS(texture_drawer);
   	else if(new_enemy_type==3)
   		enemy_type = new Officer(texture_drawer);
   	else if(new_enemy_type==4)
   		enemy_type = new Mutant(texture_drawer);
}

int Enemy:: getType(){
	return enemy_type->getType();
}

void Enemy::moving(){
	is_moving = true;
}

void Enemy::shoot(SoundPlayer& soundPlayer, float distance){
	enemy_type->shoot(soundPlayer, distance);
}

void Enemy::updateFrame(){
	enemy_type->updateShooting();
	if(is_moving){
		moved_frames_continued++;
		moved_frames_continued = moved_frames_continued%40;		
		is_moving = false;
	}else{
		moved_frames_continued = 0;
	}

}

void Enemy::draw(const std::vector<float> &distances, int n_rays){
	int first_ray = center_ray - cant_rays/2;
	int side_texture = get_num_texture(posicion,direction, player.get_position());
	for(int i=0 ; i<cant_rays ; i++){
		int num_pixel = i*64/cant_rays;
		int current_ray = first_ray + i+ n_rays;
		if((current_ray)>0 and (current_ray)<2*n_rays){
			if(distances[current_ray]>player_distance){
				enemy_type->callDrawer(first_ray + i + n_rays,player_distance ,num_pixel,side_texture,moved_frames_continued/2);
			}
		}
	}
}


Enemy::~Enemy(){
	if(enemy_type!=nullptr)
		delete enemy_type;
}