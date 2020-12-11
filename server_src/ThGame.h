#ifndef __TH_GAME__
#define __TH_GAME__

#include <Thread.h>
#include <GameModel.h>
class ThUserServer;
#include "ThUserServer.h"

class ThGame : public Thread{
private:
    GameModelServer game_model;
    int game_id;
public:
    explicit ThGame(ThUserServer& th_user_server, int map_id,
        int game_id);
    virtual void run() override;
    virtual void stop() override;
    ~ThGame();
};

#endif
