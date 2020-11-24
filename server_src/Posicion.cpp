#include "Posicion.h"

Posicion::Posicion(int posX, int posY): 
    posX(posX), posY(posY), angulo(){
}

Posicion::Posicion(int posX, int posY, Angulo angulo):
    posX(posX), posY(posY), angulo(angulo){
}

int Posicion::getPosX(){
    return posX;
}
int Posicion::getPosY(){
    return posY;
}

Angulo Posicion::getAngulo(){
    return angulo;
}

Posicion::~Posicion(){
}
