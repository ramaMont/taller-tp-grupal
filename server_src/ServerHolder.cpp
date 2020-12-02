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

}

ServerHolder::~ServerHolder(){
}
