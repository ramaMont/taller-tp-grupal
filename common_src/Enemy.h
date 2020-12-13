#ifndef __ENEMY__
#define __ENEMY__

class Mapa;
#include "Direccion.h"

#include "Sprite.h"
class Enemy : public Sprite{
private:
	std::string id;
	Coordinates direction;
	Mapa &mapa;

public:
	explicit Enemy(Coordinates posicion, int num_texture, Jugador &player ,std::string id, Mapa &map ): 
	Sprite(posicion,num_texture,player),id(id),mapa(map){
		direction.x = 0;
		direction.y = 1;
	}

	void draw(Drawer &drawer,  const std::vector<float> distances, int n_rays) override;

	void mover_en_una_direccion(Coordinates nuevaPos);

	void mover(Coordinates nuevaPos);

	void move_up(){
		Coordinates nuevaPos = posicion;
		nuevaPos.x+=0.1;
		mover(nuevaPos);
	}
	void move_down(){
		Coordinates nuevaPos = posicion;
		nuevaPos.x-=0.1;
		mover(nuevaPos);
	}
	void move_left(){
		Coordinates nuevaPos = posicion;
		nuevaPos.y+=0.1;
		mover(nuevaPos);
	}
	void move_right(){
		Coordinates nuevaPos = posicion;
		nuevaPos.y-=0.1;
		mover(nuevaPos);	
	}	


};

#endif
