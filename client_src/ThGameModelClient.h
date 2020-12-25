#ifndef __TH_GAME_MODEL_CLIENT__
#define __TH_GAME_MODEL_CLIENT__

#include "ClientGameModel.h"
#include "ThUserClient.h"

class ThGameModelClient :  public Thread , public ClientGameModel{
private:
	bool is_running;
public:
    explicit ThGameModelClient(int user_id, int map_id, int game_id);

    virtual void processProtocol(Protocol& protocol);
    virtual void run();
    virtual void stop();
    void removePlayer(int user_id);
    ~ThGameModelClient();
};

#endif
