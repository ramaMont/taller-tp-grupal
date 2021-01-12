#ifndef __CL_TH_RECEIVER__
#define __CL_TH_RECEIVER__

#include "Thread.h"

#include "Posicionable.h"

#include "Protocol.h"
#include "Socket.h"
class GameModelClient;
#include "GameModelClient.h"


class ClientHolder;
#include "ClientHolder.h"

class ClThReceiver :  public Thread{
private:
    Socket* socket;
    ClientHolder& _client_holder;
    GameModelClient* _gameModel;

public:
    explicit ClThReceiver(Socket *socket, ClientHolder& client_holder, GameModelClient* game_model_client);
    virtual void run() override;
    virtual void stop() override;
    void setGameModel(GameModelClient* gameModel);
    void processReception(Protocol& protocol);
    GameModelClient* getGameModel();
    ~ClThReceiver();
};

#endif
