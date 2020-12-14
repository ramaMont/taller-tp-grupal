#include "Jugador.h"


Jugador::Jugador(Coordinates posicion,Coordinates direction ,Mapa& mapa):
    Movable(posicion,direction,mapa){
   	mapa.agregarJugador(this);
}

Jugador::~Jugador(){

}
