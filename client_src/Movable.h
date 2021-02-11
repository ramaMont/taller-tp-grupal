#ifndef __MOVABLE__
#define __MOVABLE__

#include <Posicionable.h>

#include "coordinates.h"
class ClMap;
#include "ClMap.h"
class Direction;
#include <Direction.h>

class Ray;
#include "ray.h"

//Jugadores o enemigos
class Movable : public Posicionable{
protected:

    ClMap &map;
public:
    explicit Movable(Coordinates posicion, Coordinates direction ,ClMap& map);

    ~Movable();  
};

#endif
