#include "Direccion.h"

static const float step_size=0.1;
static float inc = 0.05;

DirAdelante::DirAdelante(){
}

Coordinates DirAdelante::mover(Jugador* jugador, Coordinates direction){
    Coordinates posActual = jugador->getPosicion();
    posActual.increment_on_direction(direction,step_size);
    return posActual;
}

DirAdelante::~DirAdelante(){
}
//------------------------------------------------------------------------------------------------
DirAtras::DirAtras(){
}

Coordinates DirAtras::mover(Jugador* jugador, Coordinates direction){
    Coordinates posActual = jugador->getPosicion();
    posActual.increment_on_direction(direction,-step_size);
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
    if(direction.y_positive()){
        posActual.increment_on_direction(new_direction,-step_size);
    }else{
        posActual.increment_on_direction(new_direction,step_size);
    }
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
    if(direction.y_positive()){
        posActual.increment_on_direction(new_direction,step_size);
    }else{
        posActual.increment_on_direction(new_direction,-step_size);
    }
    return posActual;
}

DirDerecha::~DirDerecha(){
}

//------------------------------------------------------------------------------------------------

DirRotDerecha::DirRotDerecha(){
}

Coordinates DirRotDerecha::mover(Jugador* jugador, Coordinates direction){
    Coordinates dirActual = jugador->get_direction();
    dirActual.rotate(-inc);
    jugador->set_direction(dirActual);
    return jugador->get_coordinates();
}

DirRotDerecha::~DirRotDerecha(){
}

//------------------------------------------------------------------------------------------------

DirRotIzquierda::DirRotIzquierda(){
}

Coordinates DirRotIzquierda::mover(Jugador* jugador, Coordinates direction){
    Coordinates dirActual = jugador->get_direction();
    dirActual.rotate(inc);
    jugador->set_direction(dirActual);
    return jugador->get_coordinates();
}

DirRotIzquierda::~DirRotIzquierda(){
}