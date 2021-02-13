#ifndef __TH_RECEIVER_CLIENT__
#define __TH_RECEIVER_CLIENT__

#include <ThReceiver.h>
#include <Posicionable.h>
#include <Protocol.h>
#include <Socket.h>

class GameModelClient;
#include "GameModelClient.h"
class ClientHolder;
#include "ClientHolder.h"

class ThReceiverClient :  public ThReceiver{
private:
    ClientHolder& _client_holder;
    GameModelClient* _gameModel;

public:
    explicit ThReceiverClient(Socket *socket, ClientHolder& client_holder, GameModelClient* game_model_client);
    virtual void run() override;
    virtual void stop() override;
    void setGameModel(GameModelClient* gameModel);
    virtual void processReception(Protocol& protocol) override;
    GameModelClient* getGameModel();
    ~ThReceiverClient();
};

#endif
