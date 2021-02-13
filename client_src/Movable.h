#ifndef __MOVABLE__
#define __MOVABLE__

#include <Posicionable.h>
#include <coordinates.h>
class Direction;
#include <Direction.h>

class ClientMap;
#include "ClientMap.h"
class Ray;
#include "ray.h"

//Jugadores o enemigos
class Movable : public Posicionable{
protected:

    ClientMap &map;
public:
    explicit Movable(Coordinates posicion, Coordinates direction ,ClientMap& map);

    ~Movable();  
};

#endif
