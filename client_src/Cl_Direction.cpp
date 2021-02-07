#include "Cl_Direction.h"
#include "math.h"

#include "Character.h"

static const double step_size=0.15;
static double inc = 0.15;

DirAhead::DirAhead(){
}

Coordinates DirAhead::move(Character* character, Coordinates direction){
    Coordinates posActual = character->get_position();
    posActual.increment_on_direction(direction,step_size);
    return posActual;
}

DirAhead::~DirAhead(){
}
//-----------------------------------------------------------------------------
DirBehind::DirBehind(){
}

Coordinates DirBehind::move(Character* character, Coordinates direction){
    Coordinates posActual = character->get_position();
    posActual.increment_on_direction(direction,-step_size);
    return posActual;
}

DirBehind::~DirBehind(){
}
//-----------------------------------------------------------------------------
DirLeft::DirLeft(){
}

Coordinates DirLeft::move(Character* character, Coordinates direction){
    Coordinates posActual = character->get_position();
    Coordinates new_direction = direction.get_perpendicular_direction();
    if (direction.y_positive()){
        posActual.increment_on_direction(new_direction,-step_size);
    }else{
        posActual.increment_on_direction(new_direction,step_size);
    }
    return posActual;
}

DirLeft::~DirLeft(){
}
//-----------------------------------------------------------------------------
DirRight::DirRight(){
}

Coordinates DirRight::move(Character* character, Coordinates direction){
    Coordinates posActual = character->get_position();
    Coordinates new_direction = direction.get_perpendicular_direction();
    if (direction.y_positive()){
        posActual.increment_on_direction(new_direction,step_size);
    }else{
        posActual.increment_on_direction(new_direction,-step_size);
    }
    return posActual;
}

DirRight::~DirRight(){
}

//-----------------------------------------------------------------------------

DirRotRight::DirRotRight(){
}

Coordinates DirRotRight::move(Character* character, Coordinates direction){
    Coordinates current_dir = character->getDirection();
    current_dir.rotate(-inc);
    character->setDirection(current_dir);
    return character->get_position();
}

DirRotRight::~DirRotRight(){
}

//-----------------------------------------------------------------------------

DirRotLeft::DirRotLeft(){
}

Coordinates DirRotLeft::move(Character* character, Coordinates direction){
    Coordinates current_dir = character->getDirection();
    current_dir.rotate(inc);
    character->setDirection(current_dir);
    return character->get_position();
}

DirRotLeft::~DirRotLeft(){
}
