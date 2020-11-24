#ifndef __POSICION__
#define __POSICION__

#include "Angulo.h"
#include <cstddef>


class Posicion{
private:
    int posX;
    int posY;
    Angulo angulo;
public:
    explicit Posicion(int posX, int posY);
    explicit Posicion(int posX, int posY, Angulo angulo);
    int getPosX();
    int getPosY();
    Angulo getAngulo();
    bool operator==(const Posicion& other) const{
        return (this->posX == other.posX && this->posY == other.posY);
    }
    bool operator<(const Posicion& t) const{ 
        return (this->posX < t.posX && this->posY < t.posY); 
    } 
    ~Posicion();
    struct Hash{
        size_t operator()(const Posicion& pos) const;
    };
};

#endif
