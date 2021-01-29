#ifndef __CHARACTER__
#define __CHARACTER__

#include <Posicionable.h>

#include "coordinates.h"
class ClMap;
#include "ClMap.h"
class Direction;
#include "Cl_Direction.h"

class Ray;
#include "ray.h"

class Character : public Posicionable{
protected:
	Coordinates direction;
    ClMap &map;
    int id;
    Coordinates initial_position;
    Coordinates initial_direction;
public:
    explicit Character(Coordinates posicion,Coordinates direction ,ClMap& map, int id);
    void moveInOneDirection(Direction* direccion);
    void move(Direction* direccion);
    void setDirection(Coordinates direction);
    void setInitialPosition(Coordinates initial_position);
    Coordinates getDirection() const;

    int getId();

    void die();
    virtual void resurrect();

    ~Character();  
};

#endif
