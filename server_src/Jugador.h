#ifndef __JUGADOR__
#define __JUGADOR__

#include "Posicionable.h"
#include "Posicion.h"
class Direccion;
#include "Direccion.h"
class Mapa;
#include "Mapa.h"
#include "SetArmas.h"
#include "Item.h"
#include "Arma.h"

class Jugador final : public Posicionable{
private:
	Posicion posicion_inicial;
    Mapa &mapa;
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
    explicit Jugador(Posicion posicion, Mapa& mapa);
    void mover(Direccion* direccion);
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
    ~Jugador();
    
    // Para pruebas
    int getVida();
    int getBalas();
    size_t getPuntuacion();
};

#endif
