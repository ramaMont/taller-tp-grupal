#ifndef __SPRITE__
#define __SPRITE__

class Raycasting;
#include "ray_casting.h"

class Drawer;
#include "Drawer.h"

#include <Jugador.h>

#include "Posicionable.h"

class Sprite : public Posicionable{
protected:

public:
    explicit Sprite(Coordinates posicion, int texture, Jugador &player): 
    Posicionable(posicion,texture){}
};

#endif