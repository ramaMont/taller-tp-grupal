#include "ThSender.h"

ThSender::ThSender(ThReceiver& other_receiver, int id_user):
        other_receiver(other_receiver), id_user(id_user){
}
void ThSender::run(){
    if (!operations.empty()){
        Protocol protocol = operations.front();
        operations.pop();
        other_receiver.push(protocol);
    }
}
void ThSender::push(Protocol protocol){
    operations.push(protocol);
}

int ThSender::getId(){
    return id_user;
}

ThSender::~ThSender(){
}
