#ifndef __DIRECCION__
#define __DIRECCION__

#include "coordinates.h"
#include "Player.h"
class Player;

class Direccion{
public:

    virtual Coordinates mover(Player* jugador, Coordinates direction) = 0;
    virtual ~Direccion();
};

class DirAdelante : public Direccion{
public:
    DirAdelante();
    virtual Coordinates mover(Player* jugador, Coordinates direction) override;
    virtual ~DirAdelante();
};

class DirAtras : public Direccion{
public:
    DirAtras();
    virtual Coordinates mover(Player* jugador, Coordinates direction) override;
    virtual ~DirAtras();
};

class DirIzquierda : public Direccion{
public:
    DirIzquierda();
    virtual Coordinates mover(Player* jugador, Coordinates direction) override;
    virtual ~DirIzquierda();
};

class DirDerecha : public Direccion{
public:
    DirDerecha();
    virtual Coordinates mover(Player* jugador, Coordinates direction) override;
    virtual ~DirDerecha();
};

class DirRotDerecha : public Direccion{
public:
    DirRotDerecha();
    virtual Coordinates mover(Player* jugador, Coordinates direction) override;
    virtual ~DirRotDerecha();
};

class DirRotIzquierda : public Direccion{
public:
    DirRotIzquierda();
    virtual Coordinates mover(Player* jugador, Coordinates direction) override;
    virtual ~DirRotIzquierda();
};

#endif
