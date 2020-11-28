#ifndef __DIRECCION__
#define __DIRECCION__

#include "coordinates.h"
#include "Jugador.h"
class Jugador;

class Direccion{
public:
    virtual Coordinates mover(Jugador* jugador, Coordinates direction) = 0;
};

class DirAdelante : public Direccion{
public:
    DirAdelante();
    virtual Coordinates mover(Jugador* jugador, Coordinates direction) override;
    ~DirAdelante();
};

class DirAtras : public Direccion{
public:
    DirAtras();
    virtual Coordinates mover(Jugador* jugador, Coordinates direction) override;
    ~DirAtras();
};

class DirIzquierda : public Direccion{
public:
    DirIzquierda();
    virtual Coordinates mover(Jugador* jugador, Coordinates direction) override;
    ~DirIzquierda();
};

class DirDerecha : public Direccion{
public:
    DirDerecha();
    virtual Coordinates mover(Jugador* jugador, Coordinates direction) override;
    ~DirDerecha();
};

#endif
