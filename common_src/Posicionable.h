#ifndef __POSICIONABLE__
#define __POSICIONABLE__

#include "coordinates.h"

class Posicionable{
protected:
    Coordinates posicion;
public:
    explicit Posicionable(Coordinates posicion);
    virtual Coordinates getPosicion();
    ~Posicionable();
};

#endif
