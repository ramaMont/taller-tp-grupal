#ifndef __MOVABLE__
#define __MOVABLE__

#include <Posicionable.h>

#include "coordinates.h"
class Cl_Mapa;
#include "Cl_Mapa.h"
class Direccion;
#include "Cl_Direccion.h"

class Ray;
#include "ray.h"

class Movable : public Posicionable{
protected:
	Coordinates direction;
    Cl_Mapa &mapa;
    int id;
public:
    explicit Movable(Coordinates posicion,Coordinates direction ,Cl_Mapa& mapa, int id);
    void mover_en_una_direccion(Direccion* direccion);
    void mover(Direccion* direccion);
    void set_direction(Coordinates direction);
    Coordinates get_direction() const;

    int getId(){
    	return id;
    }

    ~Movable();  
};

#endif
