#ifndef __GAMES_ADMIN__
#define __GAMES_ADMIN__

class ThGame;
#include "ThGame.h"
#include <vector>
#include <mutex>
class ThUserServer;
#include "ThUserServer.h"

class GamesAdmin{
private:
    std::mutex mutex;
    std::vector<ThGame*> games;
    int current_game_id;

    void cleanZombies();

public:
    GamesAdmin();
    void createGame(ThUserServer& th_user_server, const int& map_id);
    ~GamesAdmin();
};

#endif
