#ifndef __MOVABLE__
#define __MOVABLE__

#include <Posicionable.h>

#include "coordinates.h"
class ClMap;
#include "ClMap.h"
class Direction;
#include "Cl_Direction.h"

class Ray;
#include "ray.h"

//Jugadores o enemigos
class Movable : public Posicionable{
protected:
	Coordinates direction;
    ClMap &map;
public:
    explicit Movable(Coordinates posicion, Coordinates direction ,ClMap& map);

    ~Movable();  
};

#endif
