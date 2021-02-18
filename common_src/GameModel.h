#ifndef __GAME_MODEL__
#define __GAME_MODEL__

#include <Direction.h>

#include <map>


class GameModel{
protected:
    std::map<Protocol::direction, Direction* > directions;
    int game_id;
    
    void initDirections();
    void cleanDirections();

public:
    explicit GameModel(int game_id);

    virtual void push(Protocol protocol) = 0;
    // virtual void processProtocol(Protocol& protocol) = 0;
    // virtual void addPlayer(int player_id) = 0;
    // virtual void addPlayer(Protocol& protocol) = 0;


    // GameModel(const GameModel&) = delete;
    // GameModel(GameModel&& other) = delete;
    // GameModel& operator=(const GameModel&) = delete;
    // GameModel& operator=(GameModel&& other);
    virtual ~GameModel();
};
#endif
