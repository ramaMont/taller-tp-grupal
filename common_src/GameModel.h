#ifndef __GAME_MODEL__
#define __GAME_MODEL__

#include "Thread.h"
#include "Mapa.h"
#include "Protocol.h"
#include "Player.h"
class ThSender;
#include "ThSender.h"
#include "Mapa.h"
#include "BlockingQueue.h"

#include <atomic>
#include <map>
#include <vector>
#include <mutex>

class GameModel : public Thread{
protected:
    Mapa map;
    BlockingQueue<Protocol> operations;
    std::vector<int> id_insertion_order;
    std::map<int,Player*> players;
    std::map<Protocol::direction, Direccion* > directions;
    int game_id;
    std::mutex m;

    void updateEvent();
    void movePlayer(int player_id);
    void shoot();
    void processMove(Protocol& protocol);
    void initDirections();
    void cleanDirections();

public:
    explicit GameModel(std::string map_filename, int game_id);

    virtual void run() override = 0;
    virtual void stop() override = 0;
    void push(Protocol protocol);
    virtual void processProtocol(Protocol& protocol) = 0;

    void addPlayer(int player_id);
    Player& getPlayer(int user_id);
    Mapa& getMap();
    int getId();

    std::vector<int>& getIdsVector();

    GameModel(const GameModel&) = delete;
    GameModel(GameModel&& other) = delete;
    GameModel& operator=(const GameModel&) = delete;
    GameModel& operator=(GameModel&& other);
    virtual ~GameModel();
};
#endif
