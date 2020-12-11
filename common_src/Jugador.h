#ifndef __JUGADOR__
#define __JUGADOR__

#include "Posicionable.h"

#include "coordinates.h"
class Mapa;
#include "Mapa.h"
class Direccion;
#include "Direccion.h"

class Jugador final : public Posicionable{
private:
	Coordinates direction;
    Mapa &mapa;
public:
    explicit Jugador(Coordinates posicion,Coordinates direction ,Mapa& mapa);
    void mover_en_una_direccion(Direccion* direccion);
    void mover(Direccion* direccion);
    void set_direction(Coordinates direction);
    Coordinates get_coordinates();

    Coordinates get_direction();

    ~Jugador();  
};

#endif
