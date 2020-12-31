#include "Jugador.h"

#include "texture.h"

Jugador::Jugador(Coordinates posicion,Coordinates direction ,Cl_Mapa& mapa, int id):
    Movable(posicion,direction,mapa,id), 
    frames_since_shot(0),
    shooting(false),score(10), lives(5), health(100), ammo(20)
    {
   	mapa.agregarJugador(this);
}

Jugador::Jugador(Cl_Mapa& mapa):
    Movable(Coordinates(4,4),Coordinates(1,0),mapa,0), 
    frames_since_shot(0),shooting(false),
    score(1000), lives(5), health(98), ammo(20)
    {
      mapa.agregarJugador(this);
}

void Jugador::complete(Coordinates initial_position,Coordinates initial_direction,int player_id){
   this->posicion = initial_position;
   this->direction = initial_direction;
   this->id = player_id;
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
   texture_drawer->show_life_bar(score, lives, health, ammo);
	gun_type->call_drawer(frames_since_shot/4);
}

void Jugador::updateHealth(int amount){
	health += amount;
}

Jugador::~Jugador(){
	if(gun_type!=nullptr)
		delete gun_type;
}
