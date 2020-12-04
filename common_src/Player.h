#ifndef __JUGADOR__
#define __JUGADOR__

#include "Protocol.h"
#include "Posicionable.h"
#include "coordinates.h"
#include "Mapa.h"
class Mapa;
#include "Direccion.h"
class Direccion;

class Player final : public Posicionable{
private:
	Coordinates direction;
    Mapa &mapa;
    int player_id;
public:
    explicit Player(Coordinates position,Coordinates direction ,Mapa& mapa);
    explicit Player(Coordinates position,Coordinates direction ,Mapa& mapa, int id);
    void mover(Direccion* direccion);
    void set_direction(Coordinates direction);
    Coordinates get_coordinates();
    Coordinates get_direction();
    int getId();

    ~Player();  
};

#endif
