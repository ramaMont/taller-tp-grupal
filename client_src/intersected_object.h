#ifndef __INTERSECTED_OBJECT__
#define __INTERSECTED_OBJECT__

#include "Posicionable.h"
#include "coordinates.h"
#include "Mapa.h"
class Mapa;
#include "Direccion.h"
class Direccion;
#include "stdio.h"

//Datos necesarios para el gráfico del objeto colisionado con raycasting
class Intersected_object{
private:
	int number_line_texture;//Fila de pixeles a graficar (eje x)
    float distance;
    // A éste despues le tengo que hacer get_texture_number para saber
    // q textura usar
    Posicionable* object;
    // Si el objeto está en el eje x, el valor es 1, si está en y
    // es 2 y más oscura
    int side_division; 

public:
	//Cargo las caracteristicas del objeto colisionado (proximamente agregear n° textura)
    explicit Intersected_object(float distance_player_plane,Posicionable* object ,float position, int side);

    int get_texture(){
    	return object->get_texture();
    }

    float get_distance_player_plane();
    int get_number_line_texture();
    int get_side_division();
};

#endif
