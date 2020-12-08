#ifndef __BARREL__
#define __BARREL__

#include "Posicionable.h"

class Barrel final : public Posicionable{
private:
	bool located;

public:
    explicit Barrel(Coordinates posicion, int num_texture): 
    Posicionable(posicion){
    	type = "BARREL";
    	texture = num_texture;
    	located = false;
    }

	void spotted(){
		located = true;
	}

	bool is_spotted(){
		return located;
	}

	void disable_spotted(){
		located = false;
	}


    /*virtual void draw_yourself(Raycasting raycasting) override{
	  //raycasting.draw_wall(this)
	}*/

};

#endif
