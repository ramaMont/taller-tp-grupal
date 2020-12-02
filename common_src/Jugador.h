#ifndef __JUGADOR__
#define __JUGADOR__

#include "Posicionable.h"
#include "coordinates.h"
#include "Mapa.h"
class Mapa;
#include "Direccion.h"
class Direccion;
#include "SetArmas.h"
#include "Item.h"
#include "Arma.h"

class Jugador final : public Posicionable{
private:
    Coordinates direction;
    Mapa &mapa;
    Coordinates posicion_inicial;
    SetArmas setArmas;
    Arma* armaEquipada;
    int vidasRestantes;
    int vida;
    size_t puntuacion;
    int balas_disparadas;
    int balas_restantes;
    int enemigos_matados;
    bool llave;
    
public:
    explicit Jugador(Coordinates posicion,Coordinates direction ,Mapa& mapa);
    void mover(Direccion* direccion);
    void set_direction(Coordinates direction);
    Coordinates get_coordinates();

    Coordinates get_direction();
    explicit Jugador(Posicion posicion, Mapa& mapa);
    void disparar();
    void recibirDanio(int danio);
    bool usar(Item* item);
    bool agregarArma(Arma* arma);
    bool agregarVida(int cantidad);
    void agregarPuntos(int cantidad);
    bool agregarBalas(int cantidad);
    bool agregarLlave();
    bool estaPorMorir();
    void morir();
    bool revivir();
    bool estaVivo();
    
    // Para pruebas
    int getVida();
    int getBalas();
    size_t getPuntuacion();
    ~Jugador();  
};

#endif
