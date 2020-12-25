#include "Enemy_type.h"

#include "texture.h"


Enemy_type::Enemy_type(Texture &texture_drawer): texture_drawer(texture_drawer) {}
//--------------------------------------------------------------------------------------------------------
Dog::Dog(Texture &texture_drawer):Enemy_type(texture_drawer) {}
void Dog::call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	texture_drawer.show_dog(texture,frame%3,pos_x,distance_player_plane ,number_line_texture);
}
Dog::~Dog(){}
//--------------------------------------------------------------------------------------------------------

Guard::Guard(Texture &texture_drawer):Enemy_type(texture_drawer){}
void Guard::call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	texture_drawer.show_guard(texture,frame%4,pos_x,distance_player_plane ,number_line_texture);
}
Guard::~Guard(){}
//--------------------------------------------------------------------------------------------------------

SS::SS(Texture &texture_drawer):Enemy_type(texture_drawer){}
void SS::call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	texture_drawer.show_ss(texture,frame%4,pos_x,distance_player_plane,number_line_texture);
}
SS::~SS(){}
//--------------------------------------------------------------------------------------------------------

Officer::Officer(Texture &texture_drawer):Enemy_type(texture_drawer){}
void Officer::call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	texture_drawer.show_officer(texture,frame%4,pos_x,distance_player_plane,number_line_texture);
}
Officer::~Officer(){}
//--------------------------------------------------------------------------------------------------------

Mutant::Mutant(Texture &texture_drawer):Enemy_type(texture_drawer) {}
void Mutant::call_drawer(int pos_x, float distance_player_plane, int number_line_texture, int texture, int frame){
	texture_drawer.show_mutant(texture,frame%4,pos_x,distance_player_plane,number_line_texture);
}
Mutant::~Mutant(){}
