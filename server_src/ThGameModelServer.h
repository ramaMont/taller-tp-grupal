#ifndef __TH_GAME_MODEL_SERVER__
#define __TH_GAME_MODEL_SERVER__

#include <Thread.h>
#include <GameModel.h>
class ThUserServer;
#include "ThUserServer.h"
//class ThGameEvents;
#include "ThGameEvents.h"
class ThBots;
#include "ThBots.h"

#include <atomic>
#include <map>
#include <utility>
#include <string>
#include <vector>

class ThGameModelServer : public GameModel, public Thread{
private:
    ServerMap map;
    BlockingQueue<Protocol> operations;
    std::vector<int> id_insertion_order;
    std::map<int,Player*> players;

    std::map<int,ThSender *> users_sender;
    std::map<int, Rocket*> rockets;
    std::atomic<bool> launched;
    ThGameEvents th_game_events;
    ThBots th_bots;
    int map_id_checksum;
    int _bots_cty;
    int rocket_ids;

    void processMove(Protocol& protocol);
    void processShoot(Protocol protocol);
    void processShooted(Protocol protocol);
    void processDie(Protocol protocol);
    void processResurrect(Protocol& protocol);
    void processOpen(Protocol& protocol);
    void processOpening(Protocol& protocol);
    void processClose(Protocol& protocol);
    void processGunSwitch(Protocol& protocol);
    void processTimeRocket(Protocol& protocol);
    void processExplosion(Protocol& protocol);
    void processTopFiveEnd();
    void sendPlayerProtocol(Protocol& protocol);
    void convertToTopFive(std::vector<std::pair<int,int>>& points_vector);
    void sendTopFiveToPlayers(
        const std::vector<std::pair<int,int>>& ordered_players_kills,
        const std::vector<std::pair<int,int>>& ordered_players_points,
        const std::vector<std::pair<int,int>>& ordered_players_bullets);
    void endGame(bool isAWinner = false);
    void processWinnerEnd();
    void processProtocol(Protocol& protocol);

public:
    explicit ThGameModelServer(ThUserServer& th_user_server, std::string
        map_filename, int game_id, int map_id_checksum, int bots_cty);

    virtual void run() override;
    virtual void stop() override;
    virtual void push(Protocol protocol) override;
    void addThSender(ThSender* th_sender);
    
    // Envia el protocolo pasado por parametro a todos
    // los usuarios que se encuentren conectados a esta partida.
    void echoProtocol(Protocol protocol);

    // Elimina al jugador cuyo id coincida con el valor pasado por parametro
    // lo saca tanto del mapa de juego como del vector de ThSenders.
    void removePlayer(int user_id);
    virtual bool isDone() override;

    // Retorna verdadero si la partida está corriendo como thread 
    // o falso en caso contrario
    bool wasLaunched();
    int getMapIdChecksum();
    int getBotsCty();

    void addPlayer(int player_id);
    Player& getPlayer(int user_id);
    ServerMap& getMap();
    int getId();

    std::vector<int>& getIdsVector();

    ~ThGameModelServer();
};

#endif
