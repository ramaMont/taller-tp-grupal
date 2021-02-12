#include "ThUser.h"
#include <iostream>
//#include <ServerMap.h>
#include <vector>
#include <map>
//#include <GameModel.h>

ThUser::ThUser(int user_id): Thread(), operations(),user_id(user_id){
}

void ThUser::run(){
//    Protocol protocol = operations.pop();
}

void ThUser::push(Protocol protocol){
    operations.push(protocol);
}

int ThUser::getId(){
    return user_id;
}

void ThUser::stop(){
    is_running = false;
    operations.stop();
}

void ThUser::removePlayer(int user_id){
}

void ThUser::waitForAction(Protocol::action desired_action){
    bool ready = false;
    while (!ready){
        Protocol protocol = operations.pop();
        if (protocol.getAction() == desired_action)
            ready = true;
    }
}

ThUser::~ThUser(){
}
