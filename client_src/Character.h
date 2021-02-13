#ifndef __CHARACTER__
#define __CHARACTER__

class Movable;
#include "Movable.h"

#include <coordinates.h>
class ClientMap;
#include "ClientMap.h"
class Direction;
#include <Direction.h>

class Ray;
#include "ray.h"

#include "CharacterValues.h"

//Jugadores o enemigos
class Character : public Movable{
protected:
    int id;
    Coordinates initial_position;
    Coordinates initial_direction;
public:
    explicit Character(Coordinates posicion,Coordinates direction ,ClientMap& map, int id);

    //Pre: el personaje intentó moverse directamente y chocó contra un objeto
    // separa la direccion de movimiento en sus ejes X e Y e intenta moverse individualmente por cada uno
    void moveInOneDirection(Direction* direccion);

    //Pre:-
    // mueve al personaje
    void move(Direction* direccion);

    //Pre:-
    // modifica la direccion del personaje
    void setDirection(Coordinates direction);

    //Pre:- 
    // setea la posicion inicial  del personaje, donde va a revivir.
    void setInitialPosition(Coordinates initial_position);

    virtual CharacterType getType() = 0;

    //Pre:-
    // Se agrega a si mismo al mapa y vuelve a setear su posicion y direccion a las iniciales
    virtual void resurrect();

    Coordinates getDirection() const;

    int getId();

    ~Character();  
};

#endif
