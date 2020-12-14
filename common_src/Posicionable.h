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

class Posicionable{
protected:
    Coordinates posicion;
    int texture;
public:

	//Estos 2 no deberian estár, idealmente podria usar double dispatch y fue
	int get_texture(){
		return texture;
	}

	explicit Posicionable(Coordinates posicion);

    explicit Posicionable(Coordinates posicion,int texture);

    virtual Intersected_object colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

    virtual Coordinates getPosicion();

    virtual void add(Movable* movable){
        throw -2;
    }

    virtual void remove(){
        throw -2;
    }

    virtual ~Posicionable();
};

#endif
