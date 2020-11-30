#include "ServerHolder.h"
#include <Mapa.h>
#include <Jugador.h>
#include <coordinates.h>
#include <Direccion.h>
#include <iostream>
#include <exception>

ServerHolder::ServerHolder(int argc, char** argv):
    paramReader(argc, argv){
}

void ServerHolder::run(){
    float step_size = 0.1;
    Mapa mapa(20,20);
    float i;
    bool lugar_vacio = false;
    //Mirando hacia la izquierda
    //Poner 00 despues de la coma
    Coordinates angulo(-1,0);
    Coordinates posicionIni(11, 15);
    Jugador jugador(posicionIni, angulo, mapa);
    DirAdelante dir;
    for (i = 0.0; i < 1.0; i+=step_size)
        jugador.mover(&dir);
    Posicionable* resultado = mapa.obtenerPosicionableEn(jugador.getPosicion());
    Posicionable* vacio = mapa.obtenerPosicionableEn(posicionIni);
    if (vacio == nullptr)
        lugar_vacio = true;
    
    std::cout << resultado->getPosicion().x << std::endl;
    std::cout << posicionIni.x << std::endl;
    std::cout << resultado->getPosicion().y << std::endl;
    std::cout << posicionIni.y << std::endl;
    std::cout << lugar_vacio << std::endl;
}

ServerHolder::~ServerHolder(){
}
