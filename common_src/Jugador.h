#ifndef __JUGADOR__
#define __JUGADOR__


#include "Posicionable.h"

#include "coordinates.h"
class Mapa;
#include "Mapa.h"
class Direccion;
#include "Direccion.h"

class Movable;
#include <Movable.h>

class Jugador final : public Movable{

public:
    explicit Jugador(Coordinates posicion,Coordinates direction ,Mapa& mapa);


    ~Jugador();  
};

#endif
