#ifndef __ENEMY__
#define __ENEMY__

#include "Posicionable.h"

#include "coordinates.h"
class Mapa;
#include "Mapa.h"
class Direccion;
#include "Direccion.h"

class Movable;
#include <Movable.h>

#include "Sprite_drawer.h"

#include "Enemy_type.h"

class Enemy : public Movable, public Sprite_drawer{
private:
	Jugador &player;	
	int num_texture;
	std::string id;
	int moved_frames_continued;
	Enemy_type* enemy_type;

public:
	explicit Enemy(Texture &texture_drawer,Coordinates posicion, int num_texture, Coordinates direction ,Mapa& mapa, Jugador &player ,std::string id);

    Intersected_object colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
        spotted();
        return ray->sprite_colided(coordinates_map);
    } 

    void new_enemy_type(int new_enemy_type){
    	printf("apretaste el: %i \n", new_enemy_type);
    	if(enemy_type!=nullptr)
    		delete enemy_type;
    	if(new_enemy_type==0)
    		enemy_type = new Dog(texture_drawer);
    	else if(new_enemy_type==1)
    		enemy_type = new Guard(texture_drawer);
    	else if(new_enemy_type==2)
    		enemy_type = new SS(texture_drawer);
    	else if(new_enemy_type==3)
    		enemy_type = new Officer(texture_drawer);
    	else if(new_enemy_type==4)
    		enemy_type = new Mutant(texture_drawer);
    }

	void spotted() override{
		spotted_sprite();
	}

	void moving(){
		moved_frames_continued++;
		moved_frames_continued = moved_frames_continued%40;
	}

	void still(){
		moved_frames_continued=0;
	}


	void draw(const std::vector<float> &distances, int n_rays);

	~Enemy();

};

#endif
