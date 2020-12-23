#include "GamesAdmin.h"

#include "ThGameModelServer.h"
#include "Mapa.h"
#include <ThUser.h>
#include <coordinates.h>
#include <Player.h>

#include <map>
#include <utility>
#include <vector>

GamesAdmin::GamesAdmin(): current_game_id(0){
}

void GamesAdmin::cleanZombies(){
    std::map<int, ThGameModelServer*> activeGames;
    for (auto it = games.begin(); it != games.end(); ++it){
        auto th_game = it->second;
        if (th_game->isDone()){
            th_game->stop();
            th_game->join();
            delete(th_game);
        } else {
            activeGames.insert(std::pair<int, ThGameModelServer*>
                (th_game->getId(), th_game));
        }
    }
    games.swap(activeGames);    
}

void GamesAdmin::createGame(ThUserServer& th_user_server, const int& map_id){
    std::lock_guard<std::mutex> lck(mutex);
    cleanZombies();
    ThGameModelServer* th_game = new ThGameModelServer(th_user_server, map_id,
        current_game_id);
    games.insert(std::pair<int, ThGameModelServer*>(th_game->getId(), th_game));
    th_user_server.setGameId(current_game_id);
    ++current_game_id;
}

void GamesAdmin::launchGame(int game_id){
    games.at(game_id)->start();
}

void GamesAdmin::joinGame(ThUserServer& th_user_server, int game_id){
    std::lock_guard<std::mutex> lck(mutex);
    auto th_game = games.at(game_id);
    // Le envio al jugador los ids de todos los jugadores en orden
    // en el que fueron ingresando.
    std::vector<int>& ids_vector = th_game->getIdsVector();
    th_user_server.transmit(ids_vector);
    // Inserto al jugador nuevo en el game model
    th_game->addPlayer(th_user_server.getId());
    th_game->addThSender(th_user_server.getSender());
    th_user_server.setGameModel(th_game);
    th_user_server.setGameId(game_id);
    // Le envio a todos los jugadores que se ha unido uno nuevo.
    // Incluido el nuevo jugador asi se agrega en su modelo.
    Protocol protocol(th_user_server.getId());
    protocol.setAction(Protocol::action::ADD_PLAYER);
    th_game->echoProtocol(protocol);
}

void GamesAdmin::removePlayer(int game_id, int user_id){
    try{
        auto game = games.at(game_id);
        game->removePlayer(user_id);
    } catch(...){
    }
}

GamesAdmin::~GamesAdmin(){
    for (auto it = games.begin(); it != games.end(); ++it){
        auto th_game = it->second;
        if (th_game->wasLaunched()){
            th_game->stop();
            th_game->join();
        }
        delete(th_game);
    }
}
