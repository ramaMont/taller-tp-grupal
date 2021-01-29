#include "EnemyType.h"

#include "texture.h"


EnemyType::EnemyType(Texture *texture_drawer): texture_drawer(texture_drawer),frames_shooting(0) {}

void EnemyType::shoot(){
	frames_shooting++;
}
void EnemyType::updateShooting(){
	if(frames_shooting>0){//si es mayor que 0, estoy disparando
		frames_shooting++;
		if(frames_shooting>10){//Si es 0, terminé de disparar(lo muestro 10 frames nomas)
			frames_shooting=0;
		}
	}
}
//--------------------------------------------------------------------------------------------------------
Dog::Dog(Texture *texture_drawer):EnemyType(texture_drawer) {}
void Dog::callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	if(frames_shooting!=0){
		texture_drawer->showDog(texture,frame%3,pos_x,distance_player_plane ,number_line_texture, true);
	}else{
		texture_drawer->showDog(texture,frame%3,pos_x,distance_player_plane ,number_line_texture, false);
	}
}
Dog::~Dog(){}
//--------------------------------------------------------------------------------------------------------

Guard::Guard(Texture *texture_drawer):EnemyType(texture_drawer){}
void Guard::callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	if(frames_shooting!=0){
		texture_drawer->showGuard(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, true);
	}else{
		texture_drawer->showGuard(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, false);
	}
}
Guard::~Guard(){}
//--------------------------------------------------------------------------------------------------------

SS::SS(Texture *texture_drawer):EnemyType(texture_drawer){}
void SS::callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	if(frames_shooting!=0){
		texture_drawer->showSs(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, true);
	}else{
		texture_drawer->showSs(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, false);
	}
}
SS::~SS(){}
//--------------------------------------------------------------------------------------------------------

Officer::Officer(Texture *texture_drawer):EnemyType(texture_drawer){}
void Officer::callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	if(frames_shooting!=0){
		texture_drawer->showOfficer(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, true);
	}else{
		texture_drawer->showOfficer(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, false);
	}
}
Officer::~Officer(){}
//--------------------------------------------------------------------------------------------------------

Mutant::Mutant(Texture *texture_drawer):EnemyType(texture_drawer) {}
void Mutant::callDrawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	if(frames_shooting!=0){
		texture_drawer->showMutant(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, true);
	}else{
		texture_drawer->showMutant(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, false);
	}
}
Mutant::~Mutant(){}
