#ifndef __JUGADOR__
#define __JUGADOR__

#include "Posicionable.h"
#include "coordinates.h"
#include "Mapa.h"
class Mapa;
#include "Direccion.h"
class Direccion;
class EstadoSoldado;
#include "Soldado.h"
#include "Item.h"
#include <vector>


class Jugador final : public Posicionable{
private:
    Mapa &mapa;
    Coordinates direction;
    Coordinates posicion_inicial;
    int vidasRestantes;
    int vida;
    int balas_restantes;
    bool llave;
    EstadoSoldado soldado;
    size_t puntuacion;
    size_t balas_disparadas;
    size_t enemigos_matados;
    
public:
    explicit Jugador(Coordinates posicion,Coordinates direction ,Mapa& mapa);
    void mover(Direccion* direccion);
    void set_direction(Coordinates direction);
    Coordinates get_coordinates();

    Coordinates get_direction();
    
    void disparar(std::vector<Jugador*>&);
    bool recibirDanio(int danio);
    bool usar(Item* item);
    bool agregarArma(Arma* arma);
    void cambiarArma(int numero_arma);
    bool agregarVida(int cantidad);
    void agregarPuntos(int cantidad);
    bool agregarBalas(int cantidad);
    bool agregarLlave();
    bool usarLlave();
    void agregarEnemigoMuerto();
    bool estaPorMorir();
    void morir();
    bool revivir();
    bool estaVivo();
    Mapa& getMapa();
    size_t getBalasDisparadas();
    size_t getEnemigosMatados();
    size_t getPuntuacion();    
    ~Jugador();
    
    // Para pruebas
    int getVida();
    int getBalas(); 
};

#endif
