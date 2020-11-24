#include "ServerHolder.h"
#include "Mapa.h"
#include "Jugador.h"
#include "Posicion.h"
#include "Direccion.h"
#include <iostream>
#include <exception>

ServerHolder::ServerHolder(int argc, char** argv):
    paramReader(argc, argv){
}

void ServerHolder::run(){
    //arrange
    Mapa mapa(20,20);
    //Mirando hacia derecha
    //Poner 00 despues de la coma
    Angulo angulo(0.00);
    Posicion posicionIni2(12,0, angulo);
    Jugador jugador2(posicionIni2, mapa);
    Posicion posicionIni(11,0, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    try{
        jugador.mover(&dir);
    } catch(...) {}
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    std::cout << resultado->getPosicion().getPosX() << std::endl;
    std::cout << resultado->getPosicion().getPosY() << std::endl;
}

ServerHolder::~ServerHolder(){
}
