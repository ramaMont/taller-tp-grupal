#include "Posicion.h"

Posicion::Posicion(int posX, int posY): 
    posX(posX), posY(posY){
}

int Posicion::getPosX(){
    return posX;
}
int Posicion::getPosY(){
    return posY;
}

bool Posicion::operator==(const Posicion& other){
    return (this->posX == other.posX && this->posY == other.posY);
}



Posicion::~Posicion(){
}
