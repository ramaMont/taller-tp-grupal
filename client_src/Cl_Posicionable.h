#ifndef __POSICIONABLE__
#define __POSICIONABLE__
#include <string>

#include "coordinates.h"

class Ray;
#include "../client_src/ray.h"
class Intersected_object;
#include "../client_src/intersected_object.h"
class Movable;
class Jugador;
class Enemy;
class Texture;


class Cl_Posicionable{
protected:
    Coordinates posicion;
    Texture *texture_drawer;
public:


	explicit Cl_Posicionable(Coordinates posicion);

    void set_texture(Texture *a_texture_drawer);

	// Tira excepcion, los objetos con los que colisiono solo pueden ser clases hijas de Posicionable.
    virtual Intersected_object colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

    virtual Coordinates get_position();

    // En ningun otro objeto ademas de SpriteHolder puedo tener otro Posicionable adentro
    virtual void add(Movable* movable){
        throw -2;
    }

	// En ningun otro objeto ademas de SpriteHolder puedo tener otro Posicionable adentro
    virtual void remove(){
        throw -2;
    }

    virtual ~Cl_Posicionable();
};

#endif
