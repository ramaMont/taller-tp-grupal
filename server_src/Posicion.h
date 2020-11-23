#ifndef __POSICION__
#define __POSICION__

class Posicion{
private:
    int posX;
    int posY;
public:
    explicit Posicion(int posX, int posY);
    int getPosX();
    int getPosY();
    bool operator==(const Posicion& other);
//    bool Posicion::operator<(const Posicion& t) const;
    bool operator<(const Posicion& t) const{ 
        return (this->posX < t.posX && this->posY < t.posY); 
    } 
    ~Posicion();
};

#endif
