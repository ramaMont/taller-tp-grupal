#include "Direccion.h"
#define GRADOS_ROTACION 10.00

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

DirRotIzq::DirRotIzq(){
}

Posicion DirRotIzq::mover(Jugador* jugador){

    Posicion posActual = jugador->getPosicion();
    Angulo nuevo_angulo = posActual.getAngulo() + GRADOS_ROTACION;
    Posicion posNueva(posActual.getPosX(), posActual.getPosY(), nuevo_angulo);
    return posNueva;
}

DirRotIzq::~DirRotIzq(){
}

DirRotDer::DirRotDer(){
}

Posicion DirRotDer::mover(Jugador* jugador){

    Posicion posActual = jugador->getPosicion();
    Angulo nuevo_angulo = posActual.getAngulo() - GRADOS_ROTACION;
    Posicion posNueva(posActual.getPosX(), posActual.getPosY(), nuevo_angulo);
    return posNueva;
}

DirRotDer::~DirRotDer(){
}
