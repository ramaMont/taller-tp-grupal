#include "Angulo.h"

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

Angulo::~Angulo(){
}
