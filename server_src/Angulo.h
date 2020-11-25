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
    Angulo operator +(const double& other);
    Angulo operator -(const double& other);
    bool operator ==(const Angulo& other) const;
    ~Angulo();
};

#endif
