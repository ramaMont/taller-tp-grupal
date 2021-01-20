#include "Door.h"
#include "../client_src/texture.h"
#include "ray.h"

Door::Door(Coordinates posicion): 
    Posicionable(posicion), current_frame(0), state("closed"), movable(nullptr){}

void Door::colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
	ray->door_colided(coordinates_map,first_triangle,this);
}

void Door::add(Movable* new_movable){
	if(movable!=nullptr or (state!="open" and state!="closing")){
		throw -2;
	}else{
		movable=new_movable;
	}
}

void Door::remove(){
	movable = nullptr;
}

void Door::opening(){
	if(state=="closed"){
		state="opening";
	}
}

void Door::update_frame(){ //Me tardo 20 frames en abrirla
	if(state=="opening" or state =="open"){
		current_frame++;
		if(current_frame>20){
			state="open";
		}
	}
	if(current_frame==100){
		state="closing";
	}
	if(state=="closing" or state=="closed"){
		if(current_frame==20)
			state="closed";
		if(current_frame>0)
			current_frame--;
	}
}

int Door::get_limit_wall(){
	if(current_frame>20){
		return 0;
	}else{
		return 64-(current_frame*64/20);
	}
}

void Door::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer->show_door(ray,distance,number_line_texture,wall_side_y);
}
