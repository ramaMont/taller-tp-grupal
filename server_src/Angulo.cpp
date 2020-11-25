#include "Angulo.h"
#include <cmath>

Angulo::Angulo():angulo(0.0){
}

Angulo::Angulo(double angulo):angulo(angulo){
}

double Angulo::getAngulo(){
    return angulo;
}

int Angulo::getX(){
    if (angulo >= -66.422 && angulo <= 66.442)
        return 1;
    if ((angulo > 66.442 && angulo < 113.578) || 
            (angulo > -113.578  && angulo < -66.442))
        return 0;
    if (angulo >= 113.578)
        return -1;
    if (angulo <= -113.578)
        return -1;
    return 255;
}

int Angulo::getY(){
    if (angulo >= 23.578 && angulo <= 156.422)
        return 1;
    if ((angulo > -23.578 && angulo < 23.578) || 
            (angulo > 156.422))
        return 0;
    if (angulo >= -156.422 && angulo <= -23.578)
        return -1;
    return 255;
}

Angulo Angulo::operator +(const double& other){
    double nuevo_angulo = this->angulo + other;
    if (nuevo_angulo > 180.00){
        double calculo = std::fmod(nuevo_angulo,180.00);
        nuevo_angulo = -180.00 + calculo;
    }
    this->angulo = nuevo_angulo;
    return *this;
}

Angulo Angulo::operator -(const double& other){
    double nuevo_angulo = this->angulo - other;
    if (nuevo_angulo < -180.00){
        double calculo = std::fmod(nuevo_angulo, -180.00);
        nuevo_angulo = 180.00 + calculo;
    }
    this->angulo = nuevo_angulo;
    return *this;
}

bool Angulo::operator ==(const Angulo& other) const{
    return (this->angulo==other.angulo);
}

Angulo::~Angulo(){
}
