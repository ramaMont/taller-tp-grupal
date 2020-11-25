#ifndef __DIRECCION__
#define __DIRECCION__

#include "Posicion.h"
class Jugador;
#include "Jugador.h"

class Direccion{
public:
    virtual Posicion mover(Jugador* jugador) = 0;
};

class DirAdelante : public Direccion{
public:
    DirAdelante();
    virtual Posicion mover(Jugador* jugador) override;
    ~DirAdelante();
};

class DirAtras : public Direccion{
public:
    DirAtras();
    virtual Posicion mover(Jugador* jugador) override;
    ~DirAtras();
};

class DirRotIzq : public Direccion{
public:
    DirRotIzq();
    virtual Posicion mover(Jugador* jugador) override;
    ~DirRotIzq();
};

class DirRotDer : public Direccion{
public:
    DirRotDer();
    virtual Posicion mover(Jugador* jugador) override;
    ~DirRotDer();
};

#endif
