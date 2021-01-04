#include "Gun_type.h"

#include "texture.h"


Gun_type::Gun_type(Texture *texture_drawer,time_t fire_rate): 
		texture_drawer(texture_drawer), fire_rate(fire_rate) {}
time_t Gun_type::get_fire_rate(){
	return fire_rate;
}
//--------------------------------------------------------------------------------------------------------
Knife::Knife(Texture *texture_drawer):Gun_type(texture_drawer, 1000/2) {}	//frecuencia. 0.5 segundos
void Knife::call_drawer(int frame){
	texture_drawer->show_knife(frame);
}
Knife::~Knife(){}
//--------------------------------------------------------------------------------------------------------

Gun::Gun(Texture *texture_drawer):Gun_type(texture_drawer,1000/3){}		//frecuencia: 0.33 segundos
void Gun::call_drawer(int frame){
	texture_drawer->show_gun(frame);
}
Gun::~Gun(){}
//--------------------------------------------------------------------------------------------------------

Machine_gun::Machine_gun(Texture *texture_drawer):Gun_type(texture_drawer, 1000/0.3){} //frecuencia: 3.33 segundos
void Machine_gun::call_drawer(int frame){
	texture_drawer->show_machine_gun(frame);
}
Machine_gun::~Machine_gun(){}
//--------------------------------------------------------------------------------------------------------

Chain_gun::Chain_gun(Texture *texture_drawer):Gun_type(texture_drawer, 1000/10){}
void Chain_gun::call_drawer(int frame){
	texture_drawer->show_chain_gun(frame);
}
Chain_gun::~Chain_gun(){}

