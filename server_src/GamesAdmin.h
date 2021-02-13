#ifndef __GAMES_ADMIN__
#define __GAMES_ADMIN__

class ThGameModelServer;
#include <ThGameModelServer.h>
class ThUserServer;
#include "ThUserServer.h"

#include <map>
#include <mutex>
#include <string>

class GamesAdmin{
private:
    std::mutex mutex;
    std::map<int, ThGameModelServer*> games;
    int current_game_id;

    void cleanZombies();

public:
    GamesAdmin();
    void createGame(ThUserServer& th_user_server, 
        const std::string& map_filename, const int& map_id_checksum,
        int bots_cty);
    void launchGame(int game_id);
    void joinGame(ThUserServer& th_user_server, int game_id);
    void removePlayer(int game_id, int user_id);
    ThGameModelServer* getGame(int game_id);
    ~GamesAdmin();
};

#endif
