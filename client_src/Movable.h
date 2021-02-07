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
    ClMap &map;
    int id;
public:
    explicit Movable(Coordinates posicion ,ClMap& map, int id);

    int getId();

    ~Movable();  
};

#endif
