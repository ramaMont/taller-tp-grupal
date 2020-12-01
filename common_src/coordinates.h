#ifndef COORDINATES_H
#define COORDINATES_H

#include <vector>
#include <math.h>
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

    void increment_on_direction(Coordinates movement_direction, float inc);

    void rotate(float inc);

    void normalice_direction();

	//Perpendicular a la direccion q reciba
    Coordinates get_perpendicular_direction();

    bool x_positive()const;

    bool y_positive()const;

    bool x_whole()const;

    bool y_whole()const;

    void inc_x(float a_x);

    void inc_y(float a_y);

    bool has_element(const std::vector<std::vector<int>> &map);

    float get_distance_to_lower_side_x()const;

    float get_distance_to_higher_side_x()const;

    float get_distance_to_lower_side_y()const;

    float get_distance_to_higher_side_y()const;

    float calculate_distance(const Coordinates &a_position) const;

	// Según la direccion a la que apunta mi rayo, me fijo en una celda distinta
    int get_increase_x()const;

    int get_increase_y()const;

    // void set_x(float a_x);

    // void set_y(float a_y);

    //Compara nomas la parte "entera" de las coordenadas
    bool operator==(const Coordinates& other) const{
        return (floor(this->x) == floor(other.x) && floor(this->y) == floor(other.y));
    }
    
    //Compara nomas la parte "entera" de las coordenadas
    bool operator!=(const Coordinates& t) const{ 
        return (floor(this->x) != floor(t.x) || floor(this->y) != floor(t.y)); 
    } 

    bool operator<(const Coordinates& t) const{ 
        return (floor(this->x) < floor(t.x) && floor(this->y) < floor(t.y)); 
    }

    struct Hash{
        size_t operator()(const Coordinates& pos) const;
    };
};    

#endif
