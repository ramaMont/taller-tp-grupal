#ifndef __GAMES_ADMIN__
#define __GAMES_ADMIN__

class ThGameModelServer;
#include <ThGameModelServer.h>
#include <map>
#include <mutex>
class ThUserServer;
#include "ThUserServer.h"

class GamesAdmin{
private:
    std::mutex mutex;
    std::map<int, ThGameModelServer*> games;
    int current_game_id;

    void cleanZombies();

public:
    GamesAdmin();
    void createGame(ThUserServer& th_user_server, const int& map_id);
    void launchGame(int game_id);
    ~GamesAdmin();
};

#endif
