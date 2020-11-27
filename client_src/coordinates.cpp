
#include "coordinates.h"

#include <math.h>

Coordinates::Coordinates(){}

Coordinates::Coordinates(float a_x, float a_y): x(a_x), y(a_y) {}

void Coordinates::normalice_direction(){
    float length = sqrt(this->x * this->x + this->y * this->y);
    this->x/=length;
    this->y/=length;        
}

Coordinates Coordinates::get_perpendicular_direction(){//Perpendicular a la direccion q reciba
	Coordinates perpendicular;
	if(this->y!=0){
    	perpendicular.x = 1;
        perpendicular.y = -this->x/this->y;
        perpendicular.normalice_direction();
    }else{
       	perpendicular.x = 0;
        perpendicular.y = 1;
	}
	return perpendicular;
}    

void Coordinates::set_x(float a_x){
    this->x = a_x;
}

void Coordinates::set_y(float a_y){
	this->y = a_y;
}
