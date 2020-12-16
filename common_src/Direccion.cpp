#include "Direccion.h"
#include "math.h"
static const double step_size=0.15;
static double inc = 0.15;

DirAdelante::DirAdelante(){
}

Coordinates DirAdelante::mover(Movable* jugador, Coordinates direction){
    Coordinates posActual = jugador->get_position();
    posActual.increment_on_direction(direction,step_size);
    return posActual;
}

DirAdelante::~DirAdelante(){
}
//-----------------------------------------------------------------------------
DirAtras::DirAtras(){
}

Coordinates DirAtras::mover(Movable* jugador, Coordinates direction){
    Coordinates posActual = jugador->get_position();
    posActual.increment_on_direction(direction,-step_size);
    return posActual;
}

DirAtras::~DirAtras(){
}
//-----------------------------------------------------------------------------
DirIzquierda::DirIzquierda(){
}

Coordinates DirIzquierda::mover(Movable* jugador, Coordinates direction){
    Coordinates posActual = jugador->get_position();
    Coordinates new_direction = direction.get_perpendicular_direction();
    if (direction.y_positive()){
        posActual.increment_on_direction(new_direction,-step_size);
    }else{
        posActual.increment_on_direction(new_direction,step_size);
    }
    return posActual;
}

DirIzquierda::~DirIzquierda(){
}
//-----------------------------------------------------------------------------
DirDerecha::DirDerecha(){
}

Coordinates DirDerecha::mover(Movable* jugador, Coordinates direction){
    Coordinates posActual = jugador->get_position();
    Coordinates new_direction = direction.get_perpendicular_direction();
    if (direction.y_positive()){
        posActual.increment_on_direction(new_direction,step_size);
    }else{
        posActual.increment_on_direction(new_direction,-step_size);
    }
    return posActual;
}

DirDerecha::~DirDerecha(){
}

//-----------------------------------------------------------------------------

DirRotDerecha::DirRotDerecha(){
}

Coordinates DirRotDerecha::mover(Movable* jugador, Coordinates direction){
    Coordinates dirActual = jugador->get_direction();
    dirActual.rotate(-inc);
    jugador->set_direction(dirActual);
    return jugador->get_position();
}

DirRotDerecha::~DirRotDerecha(){
}

//-----------------------------------------------------------------------------

DirRotIzquierda::DirRotIzquierda(){
}

Coordinates DirRotIzquierda::mover(Movable* jugador, Coordinates direction){
    Coordinates dirActual = jugador->get_direction();
    dirActual.rotate(inc);
    jugador->set_direction(dirActual);
    return jugador->get_position();
}

DirRotIzquierda::~DirRotIzquierda(){
}
