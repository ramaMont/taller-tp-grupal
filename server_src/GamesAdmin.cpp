#include "GamesAdmin.h"

#include "ThGameModelServer.h"
#include "Mapa.h"
#include <ThUser.h>
#include <coordinates.h>
#include <Player.h>

#include <map>
#include <utility>
#include <vector>
#include <string>

GamesAdmin::GamesAdmin(): current_game_id(0){
}

void GamesAdmin::cleanZombies(){
    std::map<int, ThGameModelServer*> activeGames;
    for (auto it = games.begin(); it != games.end(); ++it){
        auto th_game = it->second;
        if (th_game->isDone()){
            th_game->stop();
            if (th_game->wasLaunched())
                th_game->join();
            delete(th_game);
        } else {
            activeGames.insert(std::pair<int, ThGameModelServer*>
                (th_game->getId(), th_game));
        }
    }
    games.swap(activeGames);    
}

void GamesAdmin::createGame(ThUserServer& th_user_server, 
        const std::string& map_filename, const int& map_id_checksum){
    std::lock_guard<std::mutex> lck(mutex);
    cleanZombies();
    ThGameModelServer* th_game = new ThGameModelServer(th_user_server, map_filename,
        current_game_id, map_id_checksum);
    th_game->addPlayer(th_user_server.getId());
    games.insert(std::pair<int, ThGameModelServer*>(th_game->getId(), th_game));
    th_user_server.setGameId(current_game_id);
    ++current_game_id;
}

void GamesAdmin::launchGame(int game_id){
    games.at(game_id)->start();
}

void GamesAdmin::joinGame(ThUserServer& th_user_server, int game_id){
    std::lock_guard<std::mutex> lck(mutex);
    cleanZombies();
    auto th_game = games.at(game_id);
    if (th_game->wasLaunched())
        throw -1;
    
    int map_id_checksum = th_game->getMapIdChecksum();
    int user_id = th_user_server.getId();
    // Le envio al jugador los ids de todos los jugadores en orden
    // en el que fueron ingresando.
    th_user_server.setGameId(game_id);
    std::vector<int>& ids_vector = th_game->getIdsVector();
    th_user_server.transmit(ids_vector, map_id_checksum);

    // Inserto al jugador nuevo en el game model
    th_game->addPlayer(user_id);
    th_game->addThSender(th_user_server.getSender());
    th_user_server.setGameModel(th_game);

    // Le envio a todos los jugadores que se ha unido uno nuevo.
    // Incluido el nuevo jugador asi se agrega en su modelo.

    Coordinates player_direction = th_game->getPlayer(user_id).
        get_direction();
    Coordinates player_position = th_game->getPlayer(user_id).
        get_coordinates();
    Protocol::direction prot_direction = player_direction.
        cast_to_direction();
    Protocol protocol_response(Protocol::action::ADD_PLAYER,
        user_id, prot_direction, map_id_checksum,
        player_position.x, player_position.y);  
    th_game->echoProtocol(protocol_response);
}

void GamesAdmin::removePlayer(int game_id, int user_id){
    try{
        auto game = games.at(game_id);
        game->removePlayer(user_id);
    } catch(...){
    }
}

ThGameModelServer* GamesAdmin::getGame(int game_id){
    return games.at(game_id);
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
