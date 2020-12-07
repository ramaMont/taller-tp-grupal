#include "ThUser.h"

ThUser::ThUser(int user_id, ThReceiver& th_receiver, ThSender& th_sender):
    Thread(), user_id(user_id), th_receiver(th_receiver), th_sender(th_sender){
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

void ThUser::stop(){
    is_running = false;
}

ThUser::~ThUser(){
}

ThUserClient::ThUserClient(int user_id, ThReceiver& th_receiver, ThSender& th_sender):
    ThUser(user_id, th_receiver, th_sender){
}

void ThUserClient::run(){

}

ThUserServer::ThUserServer(int user_id, ThReceiver& th_receiver, ThSender& th_sender):
    ThUser(user_id, th_receiver, th_sender){
}

void ThUserServer::run(){
    
}

ThUserClient::~ThUserClient(){
}

ThUserServer::~ThUserServer(){
}
