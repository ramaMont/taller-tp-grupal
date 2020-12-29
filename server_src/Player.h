#ifndef __JUGADOR__
#define __JUGADOR__

#include "Protocol.h"
#include "Posicionable.h"
#include "coordinates.h"

#include "Mapa.h"
//#include "MapaServer.h"
class Mapa;
#include "Direccion.h"
class Direccion;
class EstadoSoldado;
#include "Soldado.h"
#include "Item.h"
#include <vector>



class Player final : public Posicionable{
private:
    Coordinates direction;
    Mapa &mapa;
    int player_id;
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
    explicit Player(Coordinates position,Coordinates direction ,Mapa& mapa);
    explicit Player(Coordinates position,Coordinates direction ,Mapa& mapa,
        int id);
    void mover(Direccion* direccion);
    void set_direction(Coordinates direction);
    Coordinates get_coordinates() const;
    Coordinates get_direction() const;
    int getId();

    double calcularAngulo(Player* jugador);
    double calcularAngulo(const Coordinates& dir, const Coordinates& posicion);
    double calcularDistancia(Player* jugador);
    double calcularDistancia(const Coordinates& posicion);    
    void disparar(std::vector<Player*>&);
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
    int numeroArmaActual() const;
    size_t getBalasDisparadas();
    size_t getEnemigosMatados();
    size_t getPuntuacion();    

    ~Player();    
      
    // Para pruebas
    int getVida();
    int getBalas();     
};

#endif
