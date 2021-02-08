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
    
public:
    Posicionable();
    explicit Posicionable(Coordinates posicion);

    void set_texture(Texture *a_texture_drawer);


	// Tira excepcion, los objetos con los que colisiono solo pueden ser clases hijas de Posicionable.
    virtual void colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle);

    virtual Coordinates get_position();

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
