#ifndef __CL_TH_RECEIVER__
#define __CL_TH_RECEIVER__

#include "Thread.h"

#include "Posicionable.h"

#include "Protocol.h"
#include "Socket.h"
class GameModelClient;
#include "GameModelClient.h"
class GameModelClient;

class UserClient;
#include "UserClient.h"

class ClThReceiver :  public Thread{
private:
    Socket* socket;
    UserClient* _userClient;
    GameModelClient* _gameModel;

public:
    explicit ClThReceiver(Socket *socket);
    virtual void run() override;
    virtual void stop() override;
    void setUserClient(UserClient* user_client);
    void setGameModel(GameModelClient* gameModel);
    void processReception(Protocol& protocol);
    GameModelClient* getGameModel();
    ~ClThReceiver();
};

#endif
