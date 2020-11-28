#ifndef __JUGADOR__
#define __JUGADOR__

#include "Posicionable.h"
#include "coordinates.h"
#include "Mapa.h"
class Mapa;
#include "Direccion.h"
class Direccion;

class Jugador final : public Posicionable{
private:
	Coordinates direction;
    Mapa &mapa;
public:
    explicit Jugador(Coordinates posicion,Coordinates direction ,Mapa& mapa);
    void mover(Direccion* direccion);

    void rotate_left();

    void rotate_right();

    Coordinates get_coordinates();

    Coordinates get_direction();

    ~Jugador();


    
};

#endif
