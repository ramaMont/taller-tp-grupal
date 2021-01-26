#ifndef __TH_USER_SERVER__
#define __TH_USER_SERVER__

#include <ThUser.h>
#include <Protocol.h>
#include <BlockingQueue.h>
#include <ThSender.h>
class ThReceiver;
#include <ThReceiver.h>
class GamesAdmin;
#include "GamesAdmin.h"
class ThGameModelServer;
#include "ThGameModelServer.h"
#include <vector>

class ThUserServer : public ThUser{
private:
    Socket socket_peer;
    ThReceiver* th_receiver;
    ThSender* th_sender;
    GamesAdmin& games_admin;
    int game_id;

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
    ThSender* getSender();
    void setGameModel(ThGameModelServer* th_game_model);
    void setGameId(int game_id);
    void transmit(std::vector<int>& ids_vector, int map_id_checksum);
    void sendBotsPositions();
    ~ThUserServer();
};

#endif
