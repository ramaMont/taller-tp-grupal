#include "Movable.h"
#include <stdio.h>

Movable::Movable(Coordinates position, ClMap& map, int id):
        Posicionable(position), map(map), id(id){
}


int Movable::getId(){
    return id;
}

Movable::~Movable(){
}
