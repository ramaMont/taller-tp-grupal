#ifndef __DIRECCION__
#define __DIRECCION__

#include "coordinates.h"
#include "Player.h"
class Player;

class Direccion{
public:
    virtual Coordinates mover(Player* jugador, Coordinates direction) = 0;
};

class DirAdelante : public Direccion{
public:
    DirAdelante();
    virtual Coordinates mover(Player* jugador, Coordinates direction) override;
    ~DirAdelante();
};

class DirAtras : public Direccion{
public:
    DirAtras();
    virtual Coordinates mover(Player* jugador, Coordinates direction) override;
    ~DirAtras();
};

class DirIzquierda : public Direccion{
public:
    DirIzquierda();
    virtual Coordinates mover(Player* jugador, Coordinates direction) override;
    ~DirIzquierda();
};

class DirDerecha : public Direccion{
public:
    DirDerecha();
    virtual Coordinates mover(Player* jugador, Coordinates direction) override;
    ~DirDerecha();
};

class DirRotDerecha : public Direccion{
public:
    DirRotDerecha();
    virtual Coordinates mover(Player* jugador, Coordinates direction) override;
    ~DirRotDerecha();
};

class DirRotIzquierda : public Direccion{
public:
    DirRotIzquierda();
    virtual Coordinates mover(Player* jugador, Coordinates direction) override;
    ~DirRotIzquierda();
};

#endif
