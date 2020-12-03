#ifndef __POSICIONABLE__
#define __POSICIONABLE__

#include "coordinates.h"

class Posicionable{
protected:
    Coordinates posicion;
    int texture;
    bool puedo_pasar;
public:
	void set_texture(int num_texture){
		texture = num_texture;
	}
	int get_texture(){
		return texture;
	}

    explicit Posicionable(Coordinates posicion);
    virtual Coordinates getPosicion();
    bool puedoPasar();
    void puedoPasar(bool booleano);
    ~Posicionable();
};

#endif
