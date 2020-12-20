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
protected:
	Coordinates direction;
    Mapa &mapa;
public:
    explicit Movable(Texture &texture_drawer,Coordinates posicion,Coordinates direction ,Mapa& mapa);
    void mover_en_una_direccion(Direccion* direccion);
    void mover(Direccion* direccion);
    void set_direction(Coordinates direction);

	virtual void spotted(){
	}

    Coordinates get_direction() const;

    ~Movable();  
};

#endif
