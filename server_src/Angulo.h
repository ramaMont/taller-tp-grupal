#ifndef __ANGULO__
#define __ANGULO__

class Angulo{
private:
    double angulo;
public:
    Angulo();
    explicit Angulo(double angulo);
    double getAngulo();
    int getX();
    int getY();
    ~Angulo();
};

#endif
