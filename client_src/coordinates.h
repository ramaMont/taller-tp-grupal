#ifndef COORDINATES_H
#define COORDINATES_H

//Coordenadas, representan tanto posiciones como direcciones de un vector
/*Nota: como todos sus atributos son 
accedidos con tanta frecuencia que conviene hacerlos 
publicos en lugar de llenar mi código de getters y setters, capaz me conviene convertir esto en un struct*/
class Coordinates{
public:

    float x;
    float y;

    Coordinates();

    Coordinates(float a_x, float a_y);

    void normalice_direction();

	//Perpendicular a la direccion q reciba
    Coordinates get_perpendicular_direction();

    void set_x(float a_x);

    void set_y(float a_y);
};    

#endif
