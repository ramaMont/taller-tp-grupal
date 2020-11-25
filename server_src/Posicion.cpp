#include "Posicion.h"
#include <functional>

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

bool Posicion::operator!=(const Posicion& t) const{ 
    return (this->posX != t.posX || this->posY != t.posY); 
} 

Posicion::~Posicion(){
}

size_t Posicion::Hash::operator()(const Posicion& pos) const{
    size_t rowHash = std::hash<int>()(pos.posX);
    size_t colHash = std::hash<int>()(pos.posY) << 1;
    return rowHash ^ colHash;
}
