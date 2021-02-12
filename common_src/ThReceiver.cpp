#include "ThReceiver.h"
#include <iostream>

ThReceiver::ThReceiver(Socket* socket):
        socket(socket){
}

void ThReceiver::stop(){
    is_running = false;
}

ThReceiver::~ThReceiver(){
}
