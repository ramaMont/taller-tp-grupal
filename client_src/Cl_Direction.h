#ifndef __DIRECTION__
#define __DIRECTION__

#include "coordinates.h"
#include "Character.h"
class Character;

class Direction{
public:
    virtual Coordinates move(Character* character, Coordinates direction) = 0;
};

class DirAhead : public Direction{
public:
    DirAhead();
    virtual Coordinates move(Character* character, Coordinates direction) override;
    ~DirAhead();
};

class DirBehind : public Direction{
public:
    DirBehind();
    virtual Coordinates move(Character* character, Coordinates direction) override;
    ~DirBehind();
};

class DirLeft : public Direction{
public:
    DirLeft();
    virtual Coordinates move(Character* character, Coordinates direction) override;
    ~DirLeft();
};

class DirRight : public Direction{
public:
    DirRight();
    virtual Coordinates move(Character* character, Coordinates direction) override;
    ~DirRight();
};

class DirRotRight : public Direction{
public:
    DirRotRight();
    virtual Coordinates move(Character* character, Coordinates direction) override;
    ~DirRotRight();
};

class DirRotLeft : public Direction{
public:
    DirRotLeft();
    virtual Coordinates move(Character* character, Coordinates direction) override;
    ~DirRotLeft();
};

#endif
