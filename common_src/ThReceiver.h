#ifndef __TH_RECEIVER__
#define __TH_RECEIVER__

#include "Thread.h"

#include "Protocol.h"
#include "Socket.h"
class ThUser;
#include "ThUser.h"
#include "GameModel.h"

class ThReceiver :  public Thread{
private:

    Socket* socket;
    ThUser* _th_user;
    GameModel* _gameModel;

public:
    explicit ThReceiver(Socket *socket);
    virtual void run() override;

    virtual void stop();
    void setThUser(ThUser* th_user);
    void setGameModel(GameModel* gameModel);
    void processReception(Protocol& protocol);
    ~ThReceiver();
};

#endif
