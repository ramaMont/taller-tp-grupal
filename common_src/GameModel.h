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
    std::map<int,Player> players;
    std::map<Protocol::direction, Direccion* > directions;
    void updateEvent();
    void movePlayer(int player_id);
    void shoot();
    void processMove(Protocol& protocol);
    void initDirections();
    void cleanDirections();
public:
    explicit GameModel(int map_id);
    explicit GameModel(Mapa&& map);
    explicit GameModel(Mapa&& map, std::map<int,Player>&& players);
    void run();
    void push(Protocol protocol);
    virtual void processProtocol(Protocol& protocol) = 0;
    void addPlayer(Player player);
    Player& getPlayer(int user_id);
    Mapa& getMap();
    GameModel(const GameModel&) = delete;
    GameModel(GameModel&& other) = delete;
    GameModel& operator=(const GameModel&) = delete;
    GameModel& operator=(GameModel&& other);
    virtual ~GameModel();

};

class GameModelServer : public GameModel{
private:
    std::map<int,ThSender *> users_sender;
    void echoProtocol(Protocol protocol);
public:
    explicit GameModelServer(int map_id);
    explicit GameModelServer(Mapa&& map);
    virtual void processProtocol(Protocol& protocol) override;
    void addThSender(ThSender* th_sender);
    ~GameModelServer();
};

class GameModelClient : public GameModel{
public:
    explicit GameModelClient(Mapa&& map, std::map<int,Player>&& players);
    virtual void processProtocol(Protocol& protocol) override;
    ~GameModelClient();
};

#endif
