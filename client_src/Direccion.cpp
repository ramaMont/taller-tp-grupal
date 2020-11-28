#include "Direccion.h"

DirAdelante::DirAdelante(){
}

Coordinates DirAdelante::mover(Jugador* jugador, Coordinates direction){
    Coordinates posActual = jugador->getPosicion();
    posActual.increment_on_direction(direction,0.1);
    return posActual;
}

DirAdelante::~DirAdelante(){
}
//------------------------------------------------------------------------------------------------
DirAtras::DirAtras(){
}

Coordinates DirAtras::mover(Jugador* jugador, Coordinates direction){
    Coordinates posActual = jugador->getPosicion();
    posActual.increment_on_direction(direction,-0.1);
    return posActual;
}

DirAtras::~DirAtras(){
}
//------------------------------------------------------------------------------------------------
DirIzquierda::DirIzquierda(){

}

Coordinates DirIzquierda::mover(Jugador* jugador, Coordinates direction){
    Coordinates posActual = jugador->getPosicion();
    Coordinates new_direction = direction.get_perpendicular_direction();
    posActual.increment_on_direction(new_direction,-0.1);
    return posActual;
}

DirIzquierda::~DirIzquierda(){
}
//------------------------------------------------------------------------------------------------
DirDerecha::DirDerecha(){

}

Coordinates DirDerecha::mover(Jugador* jugador, Coordinates direction){
    Coordinates posActual = jugador->getPosicion();
    Coordinates new_direction = direction.get_perpendicular_direction();
    posActual.increment_on_direction(new_direction,0.1);
    return posActual;
}

DirDerecha::~DirDerecha(){
}
