#ifndef __GAME_MODEL__
#define __GAME_MODEL__

#include "Mapa.h"
#include "Protocol.h"
#include "Player.h"
class ThSender;
#include "ThSender.h"
#include "Mapa.h"
#include <queue>
#include <atomic>
#include <map>

class GameModel{
protected:
    Mapa map;
    std::queue<Protocol> operations;
    std::atomic<bool> keep_running;
    std::map<int,Player *> players;
    std::map<int,ThSender *> users_sender;
    std::map<enum direction, Direccion* > directions;
    void updateEvent();
    void movePlayer(int player_id);
    void shoot();
    void processMove(Protocol& protocol);
    void echoProtocol(Protocol protocol);
public:
    explicit GameModel(Mapa&& map);
    explicit GameModel(Mapa&& map, std::map<int,Player *>&& players, std::map<int,ThSender *>&& users_sender);
    void initDirections();
    void run();
    void push(Protocol protocol);
    virtual void processProtocol(Protocol& protocol) = 0;
    void addPlayer(Player* player);
    void addThSender(ThSender* th_sender);
    GameModel(const GameModel&) = delete;
    GameModel(GameModel&& other) = delete;
    GameModel& operator=(const GameModel&) = delete;
    GameModel& operator=(GameModel&& other);
    ~GameModel();

};

class GameModelServer : public GameModel{
public:
    explicit GameModelServer(Mapa&& map);
    explicit GameModelServer(Mapa&& map, std::map<int,Player *>&& players, std::map<int,ThSender *>&& users_sender);
    virtual void processProtocol(Protocol& protocol) override;
    ~GameModelServer();
};

class GameModelClient : public GameModel{
public:
    explicit GameModelClient(Mapa&& map);
    explicit GameModelClient(Mapa&& map, std::map<int,Player *>&& players, std::map<int,ThSender *>&& users_sender);
    virtual void processProtocol(Protocol& protocol) override;
    void draw();
    ~GameModelClient();
};

#endif
