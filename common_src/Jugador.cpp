#include "Jugador.h"


Jugador::Jugador(Texture &texture_drawer,Coordinates posicion,Coordinates direction ,Mapa& mapa):
    Movable(texture_drawer,posicion,direction,mapa), frames_since_shot(0),gun_type(nullptr),shooting(false){
   	mapa.agregarJugador(this);
}

void Jugador::new_gun_type(int new_gun_type){
   	if(gun_type!=nullptr)
   		delete gun_type;
   	if(new_gun_type==0)
   		gun_type = new Knife(texture_drawer);
   	else if(new_gun_type==1)
   		gun_type = new Gun(texture_drawer);
   	else if(new_gun_type==2)
   		gun_type = new Machine_gun(texture_drawer);
   	else if(new_gun_type==3)
   		gun_type = new Chain_gun(texture_drawer);
}

void Jugador::shoot(){
   	shooting = true;
   	if(frames_since_shot>16)
   		frames_since_shot = 8;
}

void Jugador::update_shots(){
   	if(shooting)
   		frames_since_shot++;
   	if(frames_since_shot>19){
   		frames_since_shot = 0;
   		shooting=false;
	}
}

void Jugador::draw(){
	gun_type->call_drawer(frames_since_shot/4);
}


Jugador::~Jugador(){
	if(gun_type!=nullptr)
		delete gun_type;
}
