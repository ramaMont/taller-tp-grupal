#include "Door.h"
#include "texture.h"
#include "ray.h"

#include "Enemy.h"

Door::Door(Coordinates posicion): 
    Posicionable(posicion), current_frame(0),
    		 state(closed), character(nullptr){}

void Door::colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
	ray->doorColided(coordinates_map,first_triangle,this);
}

void Door::add(Movable* new_character){
	if(character!=nullptr or state!=open){
		throw -2;
	}else{
		character=new_character;
	}
}

void Door::spottedMovable(){
	if(character!=nullptr){
		SpriteDrawer* movable = dynamic_cast<SpriteDrawer*>(character);
		movable->spottedSprite();
	}
}

void Door::remove(){
	character = nullptr;
}

void Door::setState(State new_state){
	state = new_state;
}

void Door::updateFrame(){
	if(state==opening or state ==open){
		if(current_frame<CANT_FRAMES_ANIMATION)
			current_frame++;
	}else if (state==closed){
		if(current_frame>0)
			current_frame--;
	}
}

int Door::getLimitWall(){
	return TEXTURE_LENGTH-(current_frame*TEXTURE_LENGTH/CANT_FRAMES_ANIMATION);
}

void Door::draw(int ray, float distance,\
				 int number_line_texture,bool wall_side_y){
	texture_drawer->showDoor(ray,distance,number_line_texture,wall_side_y);
}
