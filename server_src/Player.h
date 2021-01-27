#ifndef __JUGADOR__
#define __JUGADOR__

#include "Protocol.h"
#include "Posicionable.h"
#include "coordinates.h"
#include <BlockingQueue.h>
#include <atomic>

#include "Mapa.h"
class Mapa;
#include "Direccion.h"
class Direccion;
class EstadoSoldado;
#include "Soldado.h"
#include "Item.h"
#include <map>



class Player final : public Posicionable{
private:
    Coordinates direction;
    Mapa &mapa;
    int player_id;
    int vidasRestantes;
    int vida;
    int balas_restantes;
    bool llave;
    EstadoSoldado soldado;
    Coordinates posicion_inicial;
    size_t puntuacion;
    size_t balas_disparadas;
    size_t enemigos_matados;
    BlockingQueue<Protocol>& _game_model_queue;
    std::atomic<bool> is_alive;
    Coordinates initial_direction;
    
public:

    explicit Player(Mapa& mapa, int id, 
        BlockingQueue<Protocol>& game_model_queue);
    explicit Player(Coordinates position,Coordinates direction ,Mapa& mapa,
        BlockingQueue<Protocol>& game_model_queue);
    explicit Player(Coordinates position,Coordinates direction ,Mapa& mapa,
        int id, BlockingQueue<Protocol>& game_model_queue);
    void mover(Direccion* direccion);
    void set_direction(Coordinates direction);
    void set_direction(std::string direction);
    Coordinates get_coordinates() const;
    Coordinates get_direction() const;
    int getId();

    double calcularAngulo(Player* jugador);
    double calcularAngulo(const Coordinates& dir, const Coordinates& posicion);
    double calcularDistancia(Player* jugador);
    double calcularDistancia(const Coordinates& posicion);    
    void disparar(std::map<int, Player*>&);
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
    void setPosition(Coordinates position);

    ~Player();    
      
    // Para pruebas
    int getVida();
    int getBalas();     
};

#endif
