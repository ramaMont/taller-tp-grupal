#include "GamesAdmin.h"
#include "GameModel.h"
#include "Mapa.h"
#include <map>
#include <ThUser.h>
#include <coordinates.h>
#include <Player.h>

GamesAdmin::GamesAdmin(): current_game_id(0){
}

void GamesAdmin::cleanZombies(){
    std::vector<ThGame*> activeGames;
    for (size_t i = 0; i < games.size(); i++){
        if (!games[i]->isDone()){
            games[i]->join();
            delete games[i];
        } else {
            activeGames.push_back(games[i]);
        }
    }
    games.swap(activeGames);
}

void GamesAdmin::createGame(ThUserServer& th_user_server, const int& map_id){
    std::lock_guard<std::mutex> lck(mutex);
    cleanZombies();
    ThGame* th_game = new ThGame(th_user_server, map_id, current_game_id);
    games.push_back(th_game);
    th_game->start();
    ++current_game_id;

    // Mapa map(24, 24);
    // initMap(map);
    // static int pos_x = 2;
    // static int pos_y = 2;
    // Coordinates initial_position(pos_x, pos_y);
    // Coordinates initial_direction(0, 1);
    // Player player_server(initial_position, initial_direction, map_server, id);
    // GameModelServer game_model(map_id);
    // ThSender th_sender = th_user_server.getSender();
    // game_model.addPlayer();
    // game_model.addThSender(&th_sender);
    // ThGame* th_game = new ThGame(std::move(game_model));

    // GameModelServer* in_game_model = th_game->getGameModel();
    // ThReceiver* th_receiver = th_user_server.getReceiver();
    // th_receiver->addGameModel(in_game_model);
    // games.push_back(th_game);
    // th_game->start();
    // ++current_game_id;
}

GamesAdmin::~GamesAdmin(){
    cleanZombies();
}