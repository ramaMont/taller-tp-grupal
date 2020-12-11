#ifndef __TH_USER_CLIENT__
#define __TH_USER_CLIENT__

#include <ThUser.h>
#include "Protocol.h"
#include "BlockingQueue.h"
#include "ThSender.h"
class ThReceiver;
#include "ThReceiver.h"

class ThUserClient : public ThUser{
private:

    ThReceiver& th_receiver;
    ThSender& th_sender;
    GameModelClient* _game_model;

    void joinOrCreateGame();
    void processReception(Protocol& protocol);
    void createGameModel(int map_id);
    void waitUntilLaunch();
    void play();
public:
    explicit ThUserClient(int user_id, ThReceiver& th_receiver, ThSender& th_sender);
    virtual void run() override;
    ~ThUserClient();
};

#endif
