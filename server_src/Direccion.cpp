#include "Direccion.h"

DirAdelante::DirAdelante(){
}

Posicion DirAdelante::mover(Jugador* jugador){
    Posicion posActual = jugador->getPosicion();
    Posicion posNueva(posActual.getPosX()+posActual.getAngulo().getX(),
      posActual.getPosY()+posActual.getAngulo().getY(), posActual.getAngulo());
    return posNueva;
}

DirAdelante::~DirAdelante(){
}

DirAtras::DirAtras(){
}

Posicion DirAtras::mover(Jugador* jugador){
    Posicion posActual = jugador->getPosicion();
    Posicion posNueva(posActual.getPosX()-posActual.getAngulo().getX(),
      posActual.getPosY()-posActual.getAngulo().getY(), posActual.getAngulo());
    return posNueva;
}

DirAtras::~DirAtras(){
}
