#include "Door.h"
#include "../client_src/texture.h"
#include "ray.h"

#include "Enemy.h"

Door::Door(Coordinates posicion): 
    Posicionable(posicion), current_frame(0), state("closed"), character(nullptr){}

void Door::colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
	ray->doorColided(coordinates_map,first_triangle,this);
}

void Door::add(Character* new_character){
	if(character!=nullptr or state!="open"){
		throw -2;
	}else{
		character=new_character;
	}
}

void Door::spottedEnemy(){
	if(character!=nullptr){
		Enemy* enemy = dynamic_cast<Enemy*>(character);
		enemy->spottedSprite();
	}
}

void Door::remove(){
	character = nullptr;
}

void Door::setState(std::string new_state){
	state = new_state;
	//Tirar excepciones si no es ninguno de los estados admisibles? nah, cambiar x enum
}

void Door::updateFrame(){ //Me tardo 20 frames en abrirla
	if(state=="opening" or state =="open"){
		if(current_frame<20)
			current_frame++;
	}else if(state=="closed"){
		if(current_frame>0)
			current_frame--;
	}
}

int Door::getLimitWall(){
	if(current_frame>20){
		return 0;
	}else{
		return 64-(current_frame*64/20);
	}
}

void Door::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer->showDoor(ray,distance,number_line_texture,wall_side_y);
}
