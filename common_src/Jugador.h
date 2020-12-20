#ifndef __JUGADOR__
#define __JUGADOR__


#include "Posicionable.h"

#include "coordinates.h"
class Mapa;
#include "Mapa.h"
class Direccion;
#include "Direccion.h"

class Movable;
#include <Movable.h>

class Gun_type;
#include "Gun_type.h"

class Jugador final : public Movable{
private:
	int frames_since_shot;
	Gun_type* gun_type;
	bool shooting;	

public:
    explicit Jugador(Texture &texture_drawer,Coordinates posicion,Coordinates direction ,Mapa& mapa);

    void new_gun_type(int new_gun_type){
    	if(gun_type!=nullptr)
    		delete gun_type;
    	if(new_gun_type==0)
    		gun_type = new Knife(texture_drawer);
    	else if(new_gun_type==1)
    		gun_type = new Gun(texture_drawer);
    	else if(new_gun_type==2)
    		gun_type = new Machine_gun(texture_drawer);
    	else if(new_gun_type==3)
    		gun_type = new Chain_gun(texture_drawer);
    }

    void shoot(){
    	shooting = true;
    	if(frames_since_shot>16)
    		frames_since_shot = 8;
    }

    void update_shots(){
    	if(shooting)
    		frames_since_shot++;
    	if(frames_since_shot>19){
    		frames_since_shot = 0;
    		shooting=false;
    	}

    }

    void draw();

    ~Jugador();  
};

#endif
