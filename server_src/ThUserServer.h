#ifndef __TH_USER_SERVER__
#define __TH_USER_SERVER__

#include <Thread.h>
#include <Protocol.h>
#include <BlockingQueue.h>
#include <ThSender.h>
class ThReceiverServer;
#include "ThReceiverServer.h"
class GamesAdmin;
#include "GamesAdmin.h"
class ThGameModelServer;
#include "ThGameModelServer.h"
#include <vector>

class ThUserServer : public Thread{
private:
    Socket socket_peer;
    ThReceiverServer* th_receiver_server;
    ThSender* th_sender;
    GamesAdmin& games_admin;
    int game_id;
    BlockingQueue<Protocol> operations;
    int user_id;

    void initCommunication();
    void sendConfiguration();
    void processReception(Protocol& protocol);
    void respondSuccess();
    void respondSuccess(int map_id);
    void respondError();

public:
    explicit ThUserServer(int user_id, Socket&& socket_peer,
        GamesAdmin& games_admin);
    virtual void run() override;
    virtual void stop() override;
    ThSender* getSender();
    void setGameModel(ThGameModelServer* th_game_model);
    void setGameId(int game_id);
    void transmit(std::vector<int>& ids_vector, int map_id_checksum);
    void sendBotsPositions();
    void push(Protocol protocol);
    int getId();
    void removePlayer(int user_id);
    ~ThUserServer();
};

#endif
