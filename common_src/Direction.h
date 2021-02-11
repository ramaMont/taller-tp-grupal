#ifndef __DIRECTION__
#define __DIRECTION__

#include "coordinates.h"
#include "Posicionable.h"

class Direction{
public:
    virtual Coordinates 
        move(Posicionable* positionable, Coordinates direction) = 0;
    virtual ~Direction();
};

class DirForward : public Direction{
public:
    DirForward();
    virtual Coordinates 
        move(Posicionable* positionable, Coordinates direction) override;
    virtual ~DirForward();
};

class DirBackward : public Direction{
public:
    DirBackward();
    virtual Coordinates 
        move(Posicionable* positionable, Coordinates direction) override;
    virtual ~DirBackward();
};

class DirLeft : public Direction{
public:
    DirLeft();
    virtual Coordinates 
        move(Posicionable* positionable, Coordinates direction) override;
    virtual ~DirLeft();
};

class DirRight : public Direction{
public:
    DirRight();
    virtual Coordinates 
        move(Posicionable* positionable, Coordinates direction) override;
    virtual ~DirRight();
};

class DirRotRight : public Direction{
public:
    DirRotRight();
    virtual Coordinates 
        move(Posicionable* positionable, Coordinates direction) override;
    virtual ~DirRotRight();
};

class DirRotLeft : public Direction{
public:
    DirRotLeft();
    virtual Coordinates 
        move(Posicionable* positionable, Coordinates direction) override;
    virtual ~DirRotLeft();
};

#endif
