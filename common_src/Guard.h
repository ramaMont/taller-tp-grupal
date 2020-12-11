#ifndef __GUARD__
#define __GUARD__

#include "Sprite.h"
class Guard : public Sprite{
private:
	Coordinates direction;

public:
	explicit Guard(Coordinates posicion, int num_texture, Jugador &player): Sprite(posicion,num_texture,player){}

	void draw(Drawer &drawer,  const std::vector<float> distances, int n_rays) override;

	void move_up(){
		posicion.x+=0.1;
	}
	void move_down(){
		posicion.x-=0.1;	
	}
	void move_left(){
		posicion.y+=0.1;
	}
	void move_right(){
		posicion.y-=0.1;	
	}	


};

#endif
