#ifndef __JUGADOR__
#define __JUGADOR__

#include "Protocol.h"
#include "Posicionable.h"
#include "coordinates.h"
#include "AtomicCoordinates.h"
#include <BlockingQueue.h>

#include "Mapa.h"
class Mapa;
#include "Direccion.h"
class Direccion;
class SoldierState;
#include "Soldier.h"
#include "Item.h"
#include <map>


class Player final : public Posicionable{
private:
    Coordinates direction;
    Mapa &map;
    int player_id;
    int lives;
    int health;
    int bullets;
    int keys;
    SoldierState soldier;
    Coordinates posicion_inicial;
    size_t score;
    size_t fired_bullets;
    size_t killed_enemies;
    BlockingQueue<Protocol>& _game_model_queue;
    bool is_alive;
    Coordinates initial_direction;
    AtomicCoordinates atomic_dir;
    AtomicCoordinates atomic_pos;

    void throwGun();
    void throwBullets();
    void throwKey();
    
public:

    explicit Player(Mapa& mapa, int id, 
        BlockingQueue<Protocol>& game_model_queue);
    explicit Player(Coordinates position,Coordinates direction ,Mapa& map,
        BlockingQueue<Protocol>& game_model_queue);
    explicit Player(Coordinates position,Coordinates direction ,Mapa& map,
        int id, BlockingQueue<Protocol>& game_model_queue);
        
    // Mueve al jugador  en el mapa
    void mover(Direccion* direccion);
    
    // Setea la direccion
    void set_direction(Coordinates direction);
    void set_direction(std::string direction);
    Coordinates get_coordinates() const;
    Coordinates get_direction() const;
    int getId();

    // Retorna el angulo que forma el jugador con 'player'
    double calculateAngle(Player* player);
    
    // Retorna el angulo que forma el jugador con respecto a los argumentos
    double calculateAngle(const Coordinates& dir, const Coordinates& posicion);

    // Retorna la distancia entre el jugador y 'player'
    double calculateDistance(Player* player);
    
    // Retorna la distancia entre la posicion del jugador y el argumento
    double calculateDistance(const Coordinates& position);   
    
    // Dispara hacia sus enemigos
    // Retorna true en caso de disparar, y false si se lanzo un cohete
    bool shoot(std::map<int, Player*>& enemies);
    
    // Recibe el danio causado por el enemigo
    // Retorna true en caso de haber muerto,  sino false
    bool hurt(int damage);
    
    // Intenta utilizar un item, si lo usa retorna true
    bool use(Item* item);
    
    // Agrega un arma
    // Retorna true si la agrega, false si ya la tenia
    bool addGun(int gun_number);
    
    // Cambia su arma
    void switchGun(int gun_number);
    
    // Agrega vida
    // Retorna false si ya tenia la vida maxima
    bool addHealth(int amount);
    
    // Agrega puntuacion
    void addScore(int amount);
    
    // Agrega balas
    // Retorna false si ya tenia la cantidad maxima de balas
    bool addBullets(int amount);
    
    // Agrega una llave
    // Retorna true en caso de tener 2 llaves
    bool addKey();
    
    // Usa una llave
    // Retorna false en caso de no tener llave
    bool useKey();
    
    // Agrega un enemigo matado
    void addKilledEnemy();
    
    // Retorna true en caso de tener poca vida
    bool lowHealth();
    
    // Muere
    void die();
    
    // Revive, se reestablecen los valores iniciales del jugador
    bool revive();
    
    // Retorna true si el jugador esta vivo
    bool isAlive();
    
    // Retorna su mapa
    Mapa& getMap();
    
    // Retorna el numero de arma actual
    int actualGun();
    
    // Retorna la cantidad de balas disparadas
    size_t getFiredBullets();
    
    // Retorna la cantidad de enemigos matados
    size_t getKilledEnemies();
    
    // Retorna su puntuacion
    size_t getScore();    
    
    // Setea la posicion del jugador
    void setPosition(Coordinates position);
    
    // Retorna la direccion y posicion
    AtomicCoordinates& getAtomicDirection();
    AtomicCoordinates& getAtomicPosition();

    ~Player();     
};

#endif
