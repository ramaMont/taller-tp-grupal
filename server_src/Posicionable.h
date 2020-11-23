#ifndef __POSICIONABLE__
#define __POSICIONABLE__

#include "Posicion.h"

class Posicionable{
protected:
    Posicion posicion;
public:
    Posicionable(Posicion posicion);
    virtual Posicion getPosicion();
    ~Posicionable();
};

#endif
