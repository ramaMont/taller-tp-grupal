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
    bool lugar_vacio = false;
    //Mirando hacia la derecha
    Angulo angulo(0.0);
    Posicion posicionIni(11,15, angulo);
    Jugador jugador(posicionIni, mapa);
    DirAdelante dir;
    //act
    jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());

    try{
        mapa.obtenerPosicionableEn(posicionIni);
    } catch (...){
        lugar_vacio = true;
    }
    //assert
    std::cout << lugar_vacio << std::endl;
    std::cout << resultado->getPosicion().getPosX() << std::endl;
    std::cout << resultado->getPosicion().getPosY() << std::endl;
}

ServerHolder::~ServerHolder(){
}
