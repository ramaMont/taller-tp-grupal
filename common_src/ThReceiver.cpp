#include "ThReceiver.h"

ThReceiver::ThReceiver(GameModel& my_game_model):
        my_game_model(my_game_model){
}
void ThReceiver::run(){
    if (!operations.empty()){
        Protocol protocol = operations.front();
        operations.pop();
        my_game_model.push(protocol);
    }
}
void ThReceiver::push(Protocol protocol){
    operations.push(protocol);
}
ThReceiver::~ThReceiver(){
}
