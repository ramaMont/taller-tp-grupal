#include "GamesAdmin.h"

#include "ThGameModelServer.h"
#include "Mapa.h"
#include <map>
#include <ThUser.h>
#include <coordinates.h>
#include <Player.h>

GamesAdmin::GamesAdmin(): current_game_id(0){
}

void GamesAdmin::cleanZombies(){
    std::map<int, ThGameModelServer*> activeGames;
    for (auto it = games.begin(); it != games.end(); ++it){
        auto th_game = it->second;
        if (th_game->isDone()){
            th_game->join();
            delete(th_game);
        } else {
            activeGames.insert(std::pair<int, ThGameModelServer*>(th_game->getId(), th_game));
        }
    }
    games.swap(activeGames);    
}

void GamesAdmin::createGame(ThUserServer& th_user_server, const int& map_id){
    std::lock_guard<std::mutex> lck(mutex);
    cleanZombies();
    ThGameModelServer* th_game = new ThGameModelServer(th_user_server, map_id, current_game_id);
    games.insert(std::pair<int, ThGameModelServer*>(th_game->getId(), th_game));
    th_user_server.setGameId(current_game_id);
    ++current_game_id;
}

void GamesAdmin::launchGame(int game_id){
    games.at(game_id)->start();
}

GamesAdmin::~GamesAdmin(){
    cleanZombies();
}