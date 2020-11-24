#include "ServerHolder.h"
#include "Mapa.h"
#include "Jugador.h"
#include "Posicion.h"
#include "Direccion.h"
#include <iostream>

ServerHolder::ServerHolder(int argc, char** argv):
    paramReader(argc, argv){

}
void ServerHolder::run(){
    //arrange
    Mapa mapa;
    //Mirando hacia abajo
    //Poner 00 despues de la coma
    Angulo angulo(-135.00);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    std::cout << resultado->getPosicion().getPosX() << std::endl;
    std::cout << resultado->getPosicion().getPosY() << std::endl;
}

ServerHolder::~ServerHolder(){
}
