#include "GameModel.h"

#include <map>

GameModel::GameModel(int game_id):
        game_id(game_id){
    initDirections();
} 

/* 
Inicializo el diccionario directions para acceder a cada Direction 
en tiempo O(1)
 */
void GameModel::initDirections(){
    DirForward* forward = new DirForward();
    DirBackward* backward = new DirBackward();
    DirLeft* left = new DirLeft();
    DirRight* right = new DirRight();
    DirRotLeft* rotLeft = new DirRotLeft();
    DirRotRight* rotRight = new DirRotRight();
    directions[Protocol::direction::FORWARD] = forward;
    directions[Protocol::direction::BACKWARD] = backward;
    directions[Protocol::direction::LEFT] = left;
    directions[Protocol::direction::RIGHT] = right;
    directions[Protocol::direction::ROTATE_LEFT] = rotLeft;
    directions[Protocol::direction::ROTATE_RIGHT] = rotRight;
}

void GameModel::cleanDirections(){
    for (auto it = directions.begin(); it != directions.end(); ++it){
        Direction* dir = it->second;
        delete(dir);
    }
}

// GameModel& GameModel::operator=(GameModel&& other){
//     if (this == &other){
//         return *this;        // other is myself!
//     }
//     this->map = std::move(other.map);
//     this->is_running = true;
//     this->players = std::move(other.players);
//     this->directions = std::move(other.directions);
//     this->game_id = std::move(other.game_id);
//     return *this;
// }

GameModel::~GameModel(){
    cleanDirections();
}
