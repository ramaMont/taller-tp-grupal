#ifndef __TH_USER_CLIENT__
#define __TH_USER_CLIENT__

#include <ThUser.h>
#include "Protocol.h"
#include "BlockingQueue.h"
#include "ThSender.h"
class ThReceiver;
#include "ThReceiver.h"
class ThGameModelClient;
#include "ThGameModelClient.h"

class ThUserClient : public ThUser{
private:
    ThReceiver& th_receiver;
    ThSender& th_sender;
    ThGameModelClient* _th_game_model;
    bool is_creator;

    void joinOrCreateGame();
    void processReception(Protocol& protocol, bool& ready);
    void createGameModel(int map_id, int id_user, int game_id);
    void waitUntilLaunch();
    void play();
public:
    explicit ThUserClient(int user_id, ThReceiver& th_receiver, 
        ThSender& th_sender);
    virtual void run() override;
    virtual void removePlayer(int user_id) override;
    ~ThUserClient();
};

#endif
