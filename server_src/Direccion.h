#ifndef __DIRECCION__
#define __DIRECCION__

#include "Posicion.h"
class Jugador;
#include "Jugador.h"

class Direccion{
private:

public:
    virtual Posicion mover(Jugador* jugador) = 0;
};

class DirAdelante : public Direccion{
public:
    DirAdelante();
    virtual Posicion mover(Jugador* jugador);
    ~DirAdelante();
};

#endif
