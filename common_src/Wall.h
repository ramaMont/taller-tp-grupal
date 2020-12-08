#ifndef __WALL__
#define __WALL__

#include "Posicionable.h"

class Wall final : public Posicionable{

public:
    explicit Wall(Coordinates posicion, int num_texture): 
    Posicionable(posicion){
    	type = "WALL";
    	texture = num_texture;
    }

    /*virtual void draw_yourself(Raycasting raycasting) override{
	  //raycasting.draw_wall(this)
	}*/

};

#endif
