#include "Jugador.h"

Jugador::Jugador(Posicion posicion, Mapa& mapa):
        Posicionable(posicion), mapa(mapa){
    mapa.agregarJugador(this);
}
void Jugador::movAdelante(){
    
}
Jugador::~Jugador(){

}