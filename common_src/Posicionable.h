#ifndef __POSICIONABLE__
#define __POSICIONABLE__

#include "coordinates.h"

class Texture;
class Ray;
class Movable;

class Posicionable{
protected:
    Coordinates posicion;
    Texture *texture_drawer;
    bool esObstaculo;
	Coordinates direction;
    
public:
    Posicionable();
    explicit Posicionable(Coordinates posicion);
    explicit Posicionable(Coordinates posicion, Coordinates direction);

    void set_texture(Texture *a_texture_drawer);


	// Tira excepcion, los objetos con los que colisiono solo pueden ser clases hijas de Posicionable.
    virtual void colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

    virtual Coordinates get_position();

    //Agregados durante el refactor:
    virtual Coordinates get_coordinates();
    virtual Coordinates get_direction();
    virtual void setDirection(Coordinates direction);
    

    // En ningun otro objeto ademas de SpriteHolder puedo tener otro Posicionable adentro
    virtual void add(Movable* character){
        throw -2;
    }

	// En ningun otro objeto ademas de SpriteHolder puedo tener otro Posicionable adentro
    virtual void remove(){
        throw -2;
    }


    virtual Coordinates getPosicion();
//<<<<<<< HEAD
    bool atravesable();
    void atravesable(bool booleano);
    //~Posicionable();
//=======
    virtual ~Posicionable();
//>>>>>>> origin/main
};

#endif
