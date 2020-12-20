#include "Jugador.h"


Jugador::Jugador(Texture &texture_drawer,Coordinates posicion,Coordinates direction ,Mapa& mapa):
    Movable(texture_drawer,posicion,direction,mapa), frames_since_shot(0),gun_type(nullptr),shooting(false){
   	mapa.agregarJugador(this);
}

void Jugador::draw(){
	gun_type->call_drawer(frames_since_shot/4);
}


Jugador::~Jugador(){
	if(gun_type!=nullptr)
		delete gun_type;
}
