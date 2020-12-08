#ifndef __POSICIONABLE__
#define __POSICIONABLE__
#include <string>

#include "coordinates.h"

class Posicionable{
protected:
    Coordinates posicion;
    std::string type; //No debería tener esto, deberia poder resolverlo con un double dispatch en lugar de un if-else 
    int texture;
public:

	//Estos 2 no deberian estár, idealmente podria usar double dispatch y fue
	int get_texture(){
		return texture;
	}
	std::string get_type(){
		return type;
	}

    explicit Posicionable(Coordinates posicion);

    virtual void spotted(){ //Agregar excepcion

    }

    //void draw_yourself(Raycasting raycasting){}


    virtual Coordinates getPosicion();
    ~Posicionable();
};

#endif
