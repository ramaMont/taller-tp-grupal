#ifndef __TH_RECEIVER__
#define __TH_RECEIVER__

#include <queue>
#include "Protocol.h"
class GameModel;
#include "GameModel.h"

class ThReceiver{
private:
    std::queue<Protocol> operations;
    GameModel& my_game_model;
public:
    explicit ThReceiver(GameModel& my_game_model);
    void run();
    void push(Protocol protocol);
    ~ThReceiver();
};

#endif