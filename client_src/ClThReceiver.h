#ifndef __CL_TH_RECEIVER__
#define __CL_TH_RECEIVER__

#include "Thread.h"

#include "Cl_Posicionable.h"

#include "Protocol.h"
#include "Socket.h"
class ThUser;
#include "ThUser.h"
#include "ClientGameModel.h"

class ClThReceiver :  public Thread{
private:
    Socket* socket;
    ThUser* _th_user;
    ClientGameModel* _gameModel;

public:
    explicit ClThReceiver(Socket *socket);
    virtual void run() override;
    virtual void stop() override;
    void setThUser(ThUser* th_user);
    void setGameModel(ClientGameModel* gameModel);
    void processReception(Protocol& protocol);
    ClientGameModel* getGameModel();
    ~ClThReceiver();
};

#endif
