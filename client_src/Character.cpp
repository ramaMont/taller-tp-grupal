#include "Character.h"

Character::Character(Coordinates position,\
				Coordinates direction ,ClientMap& map, int id):
        Movable(position,direction,map), id(id){
}

void Character::moveInOneDirection(Direction* direccion){
    Coordinates nuevaPos = direccion->move(this,direction);

    Coordinates movimiento_unidireccional;
    movimiento_unidireccional.x = nuevaPos.x;
    movimiento_unidireccional.y = this->posicion.y;

    try{
        map.moveme(this, movimiento_unidireccional);
        this->posicion = movimiento_unidireccional;
    } catch(...){
    }

    movimiento_unidireccional.x = this->posicion.x;
    movimiento_unidireccional.y = nuevaPos.y;

    try{
        map.moveme(this, movimiento_unidireccional);
        this->posicion = movimiento_unidireccional;
    } catch(...){
    }
}

void Character::move(Direction* direccion){
    Coordinates nuevaPos = direccion->move(this,direction);
    try{
        map.moveme(this, nuevaPos);
        this->posicion = nuevaPos;
    } catch(...){
        moveInOneDirection(direccion);
    }
}

Coordinates Character::getDirection() const{
    return direction;
}

int Character::getId(){
    return id;
}

void Character::setDirection(Coordinates direction){
    this->direction = direction;
}

void Character::setInitialPosition(Coordinates initial_position){
    this->initial_position = initial_position;
}

void Character::resurrect(const Coordinates& res_pos){
    this->posicion = res_pos;
    this->direction = initial_direction;
	map.addMovable(this, this->posicion);
}

Character::~Character(){
}
