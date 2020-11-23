#ifndef __JUGADOR__
#define __JUGADOR__

#include "Posicionable.h"
#include "Posicion.h"
class Mapa;
#include "Mapa.h"

class Jugador final : public Posicionable{
private:
    Mapa &mapa;
public:
    explicit Jugador(Posicion posicion, Mapa& mapa);
    void movAdelante();
    ~Jugador();
};

#endif
