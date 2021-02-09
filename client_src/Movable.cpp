#include "Movable.h"
#include <stdio.h>

Movable::Movable(Coordinates position,Coordinates direction, ClMap& map):
        Posicionable(position), direction(direction), map(map){
}


Movable::~Movable(){
}
