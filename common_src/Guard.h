#ifndef __GUARD__
#define __GUARD__

#include "Sprite.h"
class Guard : public Sprite{
private:
	Coordinates direction;

public:
	explicit Guard(Coordinates posicion, int num_texture, Jugador &player): Sprite(posicion,num_texture,player){}

	void draw(Raycasting* raycasting,  const std::vector<float> distances, int n_rays) override;


};

#endif
