#ifndef __DIRECTION__
#define __DIRECTION__

#include "coordinates.h"
class Character;

class Direction{
public:
    virtual Coordinates move(Character* character, Coordinates direction) = 0;
    virtual  ~Direction() {};
};

class DirAhead final : public Direction{
public:
    DirAhead();
    virtual Coordinates move(Character* character, Coordinates direction) override;
    virtual  ~DirAhead() override;
};

class DirBehind final : public Direction{
public:
    DirBehind();
    virtual Coordinates move(Character* character, Coordinates direction) override;
    virtual  ~DirBehind() override;
};

class DirLeft final : public Direction{
public:
    DirLeft();
    virtual Coordinates move(Character* character, Coordinates direction) override;
    virtual  ~DirLeft() override;
};

class DirRight final : public Direction{
public:
    DirRight();
    virtual Coordinates move(Character* character, Coordinates direction) override;
    virtual  ~DirRight() override;
};

class DirRotRight final : public Direction{
public:
    DirRotRight();
    virtual Coordinates move(Character* character, Coordinates direction) override;
    virtual  ~DirRotRight() override;
};

class DirRotLeft final : public Direction{
public:
    DirRotLeft();
    virtual Coordinates move(Character* character, Coordinates direction) override;
    virtual  ~DirRotLeft() override;
};

#endif
