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
    bool key;
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
    void mover(Direccion* direccion);
    void set_direction(Coordinates direction);
    void set_direction(std::string direction);
    Coordinates get_coordinates() const;
    Coordinates get_direction() const;
    int getId();

    double calculateAngle(Player* player);
    double calculateAngle(const Coordinates& dir, const Coordinates& posicion);
    double calculateDistance(Player* player);
    double calculateDistance(const Coordinates& position);    
    bool shoot(std::map<int, Player*>&);
    bool hurt(int damage);
    bool use(Item* item);
    bool addGun(int gun_number);
    void switchGun(int gun_number);
    bool addHealth(int amount);
    void addScore(int amount);
    bool addBullets(int amount);
    bool addKey();
    bool useKey();
    void addKilledEnemy();
    bool lowHealth();
    void die();
    bool revive();
    bool isAlive();
    Mapa& getMap();
    int actualGun();
    size_t getFiredBullets();
    size_t getKilledEnemies();
    size_t getScore();    
    void setPosition(Coordinates position);
    AtomicCoordinates& getAtomicDirection();
    AtomicCoordinates& getAtomicPosition();

    ~Player();     
};

#endif
