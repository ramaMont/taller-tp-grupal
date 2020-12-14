#ifndef __MOVABLE__
#define __MOVABLE__

#include "Posicionable.h"

#include "coordinates.h"
class Mapa;
#include "Mapa.h"
class Direccion;
#include "Direccion.h"

class Ray;
#include "ray.h"

class Movable : public Posicionable{
private:
	Coordinates direction;
    Mapa &mapa;
public:
    explicit Movable(Coordinates posicion,Coordinates direction ,Mapa& mapa);
    void mover_en_una_direccion(Direccion* direccion);
    void mover(Direccion* direccion);
    void set_direction(Coordinates direction);

	virtual void spotted(){
	}

    Coordinates get_coordinates();

    Coordinates get_direction();

    ~Movable();  
};

#endif
