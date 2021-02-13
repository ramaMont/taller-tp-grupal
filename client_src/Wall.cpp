#include "Wall.h"
#include "texture.h"

Wall::Wall(Coordinates posicion): 
    Posicionable(posicion){}

void Wall::colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
	ray->wallColided(coordinates_map,first_triangle,this);
}
//--------------------------------------------------------------------------------------------------------

WallGreystone::WallGreystone(Coordinates posicion): 
Wall(posicion) {}

void WallGreystone::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer->showWallGreystone(ray,distance,number_line_texture,wall_side_y);
}
//--------------------------------------------------------------------------------------------------------

WallBluestone::WallBluestone(Coordinates posicion): 
Wall(posicion) {}

void WallBluestone::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer->showWallBluestone(ray,distance,number_line_texture,wall_side_y);
}
//--------------------------------------------------------------------------------------------------------

WallPurplestone::WallPurplestone(Coordinates posicion): 
Wall(posicion) {}

void WallPurplestone::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer->showWallPurplestone(ray,distance,number_line_texture,wall_side_y);
}
//--------------------------------------------------------------------------------------------------------

WallColorstone::WallColorstone(Coordinates posicion): 
Wall(posicion) {}

void WallColorstone::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer->showWallColorstone(ray,distance,number_line_texture,wall_side_y);
}
//--------------------------------------------------------------------------------------------------------

WallEagle::WallEagle(Coordinates posicion): 
Wall(posicion) {}

void WallEagle::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer->showWallEagle(ray,distance,number_line_texture,wall_side_y);
}
//--------------------------------------------------------------------------------------------------------

WallMossy::WallMossy(Coordinates posicion): 
Wall(posicion) {}

void WallMossy::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer->showWallMossy(ray,distance,number_line_texture,wall_side_y);
}
//--------------------------------------------------------------------------------------------------------

WallRedbrick::WallRedbrick(Coordinates posicion): 
Wall(posicion) {}

void WallRedbrick::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer->showWallRedbrick(ray,distance,number_line_texture,wall_side_y);
}
//--------------------------------------------------------------------------------------------------------

WallWood::WallWood(Coordinates posicion): 
Wall(posicion) {}

void WallWood::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer->showWallWood(ray,distance,number_line_texture,wall_side_y);
}
