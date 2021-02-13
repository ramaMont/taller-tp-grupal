#include "Direction.h"

#include "math.h"

const double step_size=0.15;
const double inc = 0.15;


Direction::~Direction(){
}
//-----------------------------------------------------------------------------
DirForward::DirForward(){
}

Coordinates DirForward::move(Posicionable* posicionable, Coordinates direction){
    Coordinates current_pos = posicionable->getPosicion();
    current_pos.increment_on_direction(direction,step_size);
    return current_pos;
}

DirForward::~DirForward(){
}
//-----------------------------------------------------------------------------
DirBackward::DirBackward(){
}

Coordinates DirBackward::move(Posicionable* posicionable, 
        Coordinates direction){
    Coordinates current_pos = posicionable->getPosicion();
    current_pos.increment_on_direction(direction,-step_size);
    return current_pos;
}

DirBackward::~DirBackward(){
}
//-----------------------------------------------------------------------------
DirLeft::DirLeft(){
}

Coordinates DirLeft::move(Posicionable* posicionable, Coordinates direction){
    Coordinates current_pos = posicionable->getPosicion();
    Coordinates new_direction = direction.get_perpendicular_direction();
    if (direction.y_positive()){
        current_pos.increment_on_direction(new_direction,-step_size);
    }else{
        current_pos.increment_on_direction(new_direction,step_size);
    }
    return current_pos;
}

DirLeft::~DirLeft(){
}
//-----------------------------------------------------------------------------
DirRight::DirRight(){
}

Coordinates DirRight::move(Posicionable* posicionable, Coordinates direction){
    Coordinates current_pos = posicionable->getPosicion();
    Coordinates new_direction = direction.get_perpendicular_direction();
    if (direction.y_positive()){
        current_pos.increment_on_direction(new_direction,step_size);
    }else{
        current_pos.increment_on_direction(new_direction,-step_size);
    }
    return current_pos;
}

DirRight::~DirRight(){
}

//-----------------------------------------------------------------------------

DirRotRight::DirRotRight(){
}

Coordinates DirRotRight::move(Posicionable* posicionable, 
        Coordinates direction){
    Coordinates dirActual = posicionable->get_direction();
    dirActual.rotate(-inc);
    posicionable->setDirection(dirActual);
    return posicionable->get_coordinates();
}

DirRotRight::~DirRotRight(){
}

//-----------------------------------------------------------------------------

DirRotLeft::DirRotLeft(){
}

Coordinates DirRotLeft::move(Posicionable* posicionable, 
        Coordinates direction){
    Coordinates dirActual = posicionable->get_direction();
    dirActual.rotate(inc);
    posicionable->setDirection(dirActual);
    return posicionable->get_coordinates();
}

DirRotLeft::~DirRotLeft(){
}
