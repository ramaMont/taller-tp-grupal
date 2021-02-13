#include "Movable.h"


Movable::Movable(Coordinates position,Coordinates direction, ClientMap& map):
        Posicionable(position, direction), map(map){
}

Movable::~Movable(){
}
