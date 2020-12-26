#ifndef __TH_GAME_MODEL_CLIENT__
#define __TH_GAME_MODEL_CLIENT__

#include "ClientGameModel.h"
#include "ThUserClient.h"
#include <Protocol.h>

class ThGameModelClient : public ClientGameModel{
private:
	bool is_running;
    std::queue<Protocol> operations;
public:
    explicit ThGameModelClient(int user_id, int map_id, int game_id, int protagonist_id);

    virtual void processProtocol(Protocol& protocol);
    void run();
    virtual void push(Protocol protocol) override;
    void removePlayer(int user_id);
    ~ThGameModelClient();
};

#endif
