#ifndef __TH_RECEIVER_SERVER__
#define __TH_RECEIVER_SERVER__

#include <Protocol.h>
class ThGameModelServer;
#include "ThGameModelServer.h"
#include <ThReceiver.h>
class ThUserServer;
#include "ThUserServer.h"

class ThReceiverServer :  public ThReceiver{
private:
    ThUserServer* _th_user_server;
    ThGameModelServer* _gameModel;

public:
    explicit ThReceiverServer(Socket *socket);
    virtual void run() override;
    virtual void stop() override;
    void setThUser(ThUserServer* th_user_server);
    void setGameModel(ThGameModelServer* gameModel);
    virtual void processReception(Protocol& protocol) override;
    GameModel* getGameModel();
    ~ThReceiverServer();
};

#endif
