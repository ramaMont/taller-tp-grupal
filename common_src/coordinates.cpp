
#include "coordinates.h"
#include <vector>
#include <math.h>
#include "stdio.h"
Coordinates::Coordinates(){}

Coordinates::Coordinates(double a_x, double a_y): x(a_x), y(a_y) {}

void Coordinates::increment_on_direction(Coordinates movement_direction,
		double inc){
	x+= movement_direction.x*inc;
    y+= movement_direction.y*inc;
}

void Coordinates::rotate(double inc){
	this->x = this->x*cos(inc) - this->y*sin(inc);
    this->y = this->x*sin(inc) + this->y*cos(inc);
    normalice_direction();
}

bool Coordinates::x_positive()const {
	return(this->x > 0);
}

bool Coordinates::y_positive()const {
	return(this->y > 0);
}

bool Coordinates::x_whole()const{
	return( (this->x == floor(this->x)) and (this->x == ceil(this->x)));
}

bool Coordinates::y_whole()const{
	return( (this->y == floor(this->y)) and (this->y == ceil(this->y)));
}

void Coordinates::normalice_direction(){
    double length = sqrt(this->x * this->x + this->y * this->y);
    this->x/=length;
    this->y/=length;        
}

Coordinates Coordinates::get_perpendicular_direction()const {
	//Perpendicular a la direccion q reciba
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


void Coordinates::inc_x(double a_x){
	this->x+=a_x;
}

void Coordinates::inc_y(double a_y){
	this->y+=a_y;
}

double Coordinates::get_distance_to_lower_side_x()const{
	return (floor(x+1) - x);
}

double Coordinates::get_distance_to_higher_side_x()const{
	return (ceil(x-1) - x);
}

double Coordinates::get_distance_to_lower_side_y()const{
	return (floor(y+1) - y);
}

double Coordinates::get_distance_to_higher_side_y()const{
	return (ceil(y-1) - y);
}

double Coordinates::calculate_distance(const Coordinates &a_position) const{
	return (sqrt(pow(std::abs(x-a_position.x),2) + 
		pow(std::abs(y-a_position.y),2)));
}

int Coordinates::get_increase_x()const{
	int increase = 0;
	if(!x_positive()){
		increase = -1;
	}
	return increase;
}

int Coordinates::get_increase_y()const{
	int increase = 0;
	if(!y_positive()){
		increase = -1;
	}
	return increase;
}


double Coordinates::calculate_distance_to_vector(const Coordinates vector_direction, const Coordinates vector_position){

	float num = vector_direction.x*(this->x - vector_position.x) + vector_direction.y*( this->y - vector_position.y);
	float denom = vector_direction.x*vector_direction.x + vector_direction.y*vector_direction.y;
	float n = num/denom;

	Coordinates colision_line = vector_position;
	colision_line.x+=n*vector_direction.x;
	colision_line.y+=n*vector_direction.y;

	return sqrt(pow(colision_line.x - this->x,2) + pow(colision_line.y - this->y,2));

}

// void Coordinates::set_x(double a_x){
//     this->x = a_x;
// }

// void Coordinates::set_y(double a_y){
// 	this->y = a_y;
// }

size_t Coordinates::Hash::operator()(const Coordinates& pos) const{
    size_t rowHash = std::hash<int>()((int)pos.x);
    size_t colHash = std::hash<int>()((int)pos.y) << 1;
    return rowHash ^ colHash;
}

