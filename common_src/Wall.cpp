#include "Wall.h"
#include "../client_src/texture.h"

Wall::Wall(Texture &texture_drawer,Coordinates posicion): 
    Posicionable(texture_drawer,posicion){}

Intersected_object Wall::colisioned(Ray* ray,Coordinates coordinates_map,bool first_triangle){
	return ray->wall_colided(coordinates_map,first_triangle,this);
}
//--------------------------------------------------------------------------------------------------------

Wall_greystone::Wall_greystone(Texture &texture_drawer,Coordinates posicion): 
Wall(texture_drawer,posicion) {}

void Wall_greystone::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer.show_wall_greystone(ray,distance,number_line_texture,wall_side_y);
}
//--------------------------------------------------------------------------------------------------------

Wall_bluestone::Wall_bluestone(Texture &texture_drawer,Coordinates posicion): 
Wall(texture_drawer,posicion) {}

void Wall_bluestone::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer.show_wall_bluestone(ray,distance,number_line_texture,wall_side_y);
}
//--------------------------------------------------------------------------------------------------------

Wall_purplestone::Wall_purplestone(Texture &texture_drawer,Coordinates posicion): 
Wall(texture_drawer,posicion) {}

void Wall_purplestone::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer.show_wall_purplestone(ray,distance,number_line_texture,wall_side_y);
}
//--------------------------------------------------------------------------------------------------------

Wall_colorstone::Wall_colorstone(Texture &texture_drawer,Coordinates posicion): 
Wall(texture_drawer,posicion) {}

void Wall_colorstone::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer.show_wall_colorstone(ray,distance,number_line_texture,wall_side_y);
}
//--------------------------------------------------------------------------------------------------------

Wall_eagle::Wall_eagle(Texture &texture_drawer,Coordinates posicion): 
Wall(texture_drawer,posicion) {}

void Wall_eagle::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer.show_wall_eagle(ray,distance,number_line_texture,wall_side_y);
}
//--------------------------------------------------------------------------------------------------------

Wall_mossy::Wall_mossy(Texture &texture_drawer,Coordinates posicion): 
Wall(texture_drawer,posicion) {}

void Wall_mossy::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer.show_wall_mossy(ray,distance,number_line_texture,wall_side_y);
}
//--------------------------------------------------------------------------------------------------------

Wall_redbrick::Wall_redbrick(Texture &texture_drawer,Coordinates posicion): 
Wall(texture_drawer,posicion) {}

void Wall_redbrick::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer.show_wall_redbrick(ray,distance,number_line_texture,wall_side_y);
}
//--------------------------------------------------------------------------------------------------------

Wall_wood::Wall_wood(Texture &texture_drawer,Coordinates posicion): 
Wall(texture_drawer,posicion) {}

void Wall_wood::draw(int ray, float distance, int number_line_texture,bool wall_side_y){
	texture_drawer.show_wall_wood(ray,distance,number_line_texture,wall_side_y);
}