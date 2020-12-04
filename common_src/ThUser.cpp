#include "ThUser.h"



ThUser::ThUser(int user_id, ThReceiver& th_receiver, ThSender& th_sender):
    user_id(user_id), th_receiver(th_receiver), th_sender(th_sender){
}
void ThUser::run(){
    if (!operations.empty()){
        Protocol protocol = operations.front();
        operations.pop();
        th_sender.push(protocol);
    }
}

void ThUser::push(Protocol protocol){
    operations.push(protocol);
}

int ThUser::getId(){
    return user_id;
}

ThUser::~ThUser(){
}
