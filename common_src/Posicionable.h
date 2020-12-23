#ifndef __POSICIONABLE__
#define __POSICIONABLE__

#include "coordinates.h"

class Posicionable{
protected:
    Coordinates posicion;
    int texture;
public:
	void set_texture(int num_texture){
		texture = num_texture;
	}
	int get_texture(){
		return texture;
	}

    explicit Posicionable(Coordinates posicion);
    virtual Coordinates getPosicion();
    virtual ~Posicionable();
};

#endif
