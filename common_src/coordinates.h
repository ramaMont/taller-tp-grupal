#ifndef COORDINATES_H
#define COORDINATES_H

#include <vector>
#include <math.h>
#include <string>
#include <Protocol.h>
#include <tuple>

//Coordenadas, representan tanto posiciones como direcciones de un vector
/*Nota: como todos sus atributos son 
accedidos con tanta frecuencia que conviene hacerlos 
publicos en lugar de llenar mi código de getters y setters, capaz me conviene 
convertir esto en un struct*/
class Coordinates{
public:
    double x;
    double y;

    Coordinates();
    
    explicit Coordinates(Protocol::direction direction);

    explicit Coordinates(std::string direction);

    explicit Coordinates(double a_x, double a_y);
    
    explicit Coordinates(std::tuple<int, int> position);  
  
    explicit Coordinates(std::tuple<float, float> position);

    void increment_on_direction(Coordinates movement_direction, double inc);

    void rotate(double inc);

    void normalice_direction();

	//Perpendicular a la direccion q reciba
    Coordinates get_perpendicular_direction() const;

    bool x_positive()const;

    bool y_positive()const;

    bool x_whole()const;

    bool y_whole()const;

    void inc_x(double a_x);

    void inc_y(double a_y);

    bool has_element(const std::vector<std::vector<int>> &map);

    double get_distance_to_lower_side_x()const;

    double get_distance_to_higher_side_x()const;

    double get_distance_to_lower_side_y()const;

    double get_distance_to_higher_side_y()const;

    double calculate_distance_to_vector(const Coordinates vector_direction, 
        const Coordinates vector_position);

    double calculate_distance(const Coordinates &a_position) const;

    Protocol::direction cast_to_direction();

	//Según la direccion a la que apunta mi rayo, me fijo en una celda distinta
    int get_increase_x()const;

    int get_increase_y()const;

    // Devuelve el angulo entre la direccion y la posicion desde mis coordenadas
    double calculate_angle(const Coordinates& direction, 
        const Coordinates& position) const;

    // void set_x(double a_x);

    // void set_y(double a_y);

    //Compara nomas la parte "entera" de las coordenadas
    bool operator==(const Coordinates& other) const{
        return (floor(this->x) == floor(other.x) && 
            floor(this->y) == floor(other.y));
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
