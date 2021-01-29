#ifndef __CHARACTER__
#define __CHARACTER__

#include <Posicionable.h>

#include "coordinates.h"
class ClMap;
#include "ClMap.h"
class Direccion;
#include "Cl_Direccion.h"

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
    void move_in_one_direction(Direccion* direccion);
    void mover(Direccion* direccion);
    void set_direction(Coordinates direction);
    void setInitialPosition(Coordinates initial_position);
    Coordinates get_direction() const;

    int getId();

    void die();
    virtual void resurrect();

    ~Character();  
};

#endif
