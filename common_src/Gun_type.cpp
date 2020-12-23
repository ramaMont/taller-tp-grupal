#include "Gun_type.h"

#include "texture.h"


Gun_type::Gun_type(Texture &texture_drawer): texture_drawer(texture_drawer) {}
//--------------------------------------------------------------------------------------------------------
Knife::Knife(Texture &texture_drawer):Gun_type(texture_drawer) {}
void Knife::call_drawer(int frame){
	texture_drawer.show_knife(frame);
}
Knife::~Knife(){}
//--------------------------------------------------------------------------------------------------------

Gun::Gun(Texture &texture_drawer):Gun_type(texture_drawer){}
void Gun::call_drawer(int frame){
	texture_drawer.show_gun(frame);
}
Gun::~Gun(){}
//--------------------------------------------------------------------------------------------------------

Machine_gun::Machine_gun(Texture &texture_drawer):Gun_type(texture_drawer){}
void Machine_gun::call_drawer(int frame){
	texture_drawer.show_machine_gun(frame);
}
Machine_gun::~Machine_gun(){}
//--------------------------------------------------------------------------------------------------------

Chain_gun::Chain_gun(Texture &texture_drawer):Gun_type(texture_drawer){}
void Chain_gun::call_drawer(int frame){
	texture_drawer.show_chain_gun(frame);
}
Chain_gun::~Chain_gun(){}
