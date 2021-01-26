#include "Enemy_type.h"

#include "texture.h"


Enemy_type::Enemy_type(Texture *texture_drawer): texture_drawer(texture_drawer),frames_shooting(0) {}

void Enemy_type::shoot(){
	frames_shooting++;
}
void Enemy_type::update_shooting(){
	if(frames_shooting>0){//si es mayor que 0, estoy disparando
		frames_shooting++;
		if(frames_shooting>10){//Si es 0, terminé de disparar(lo muestro 10 frames nomas)
			frames_shooting=0;
		}
	}
}
//--------------------------------------------------------------------------------------------------------
Dog::Dog(Texture *texture_drawer):Enemy_type(texture_drawer) {}
void Dog::call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	if(frames_shooting!=0){
		texture_drawer->show_dog(texture,frame%3,pos_x,distance_player_plane ,number_line_texture, true);
	}else{
		texture_drawer->show_dog(texture,frame%3,pos_x,distance_player_plane ,number_line_texture, false);
	}
}
Dog::~Dog(){}
//--------------------------------------------------------------------------------------------------------

Guard::Guard(Texture *texture_drawer):Enemy_type(texture_drawer){}
void Guard::call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	if(frames_shooting!=0){
		texture_drawer->show_guard(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, true);
	}else{
		texture_drawer->show_guard(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, false);
	}
}
Guard::~Guard(){}
//--------------------------------------------------------------------------------------------------------

SS::SS(Texture *texture_drawer):Enemy_type(texture_drawer){}
void SS::call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	if(frames_shooting!=0){
		texture_drawer->show_ss(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, true);
	}else{
		texture_drawer->show_ss(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, false);
	}
}
SS::~SS(){}
//--------------------------------------------------------------------------------------------------------

Officer::Officer(Texture *texture_drawer):Enemy_type(texture_drawer){}
void Officer::call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	if(frames_shooting!=0){
		texture_drawer->show_officer(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, true);
	}else{
		texture_drawer->show_officer(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, false);
	}
}
Officer::~Officer(){}
//--------------------------------------------------------------------------------------------------------

Mutant::Mutant(Texture *texture_drawer):Enemy_type(texture_drawer) {}
void Mutant::call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	if(frames_shooting!=0){
		texture_drawer->show_mutant(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, true);
	}else{
		texture_drawer->show_mutant(texture,frame%4,pos_x,distance_player_plane ,number_line_texture, false);
	}
}
Mutant::~Mutant(){}
