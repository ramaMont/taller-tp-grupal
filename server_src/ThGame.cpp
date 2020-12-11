#include "ThGame.h"

ThGame::ThGame(ThUserServer& th_user_server, int map_id,
            int game_id):
        Thread(), game_model(map_id), game_id(game_id){
}

void ThGame::run(){

}

void ThGame::stop(){

}

ThGame::~ThGame(){
}
