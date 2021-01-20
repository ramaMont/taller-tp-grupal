#include "ThGameEvents.h"
#include <thread>
#include <chrono>
#include <sys/time.h>
#include <iostream>

ThGameEvents::ThGameEvents(BlockingQueue<Protocol>& game_model_queue):
    Thread(), _game_model_queue(game_model_queue){
}

void ThGameEvents::run(){
    is_running = true;
    
    time_t rate = 1000/10;
    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    
    while (is_running){
        gettimeofday(&time_now, nullptr);
        time_t time = (time_now.tv_usec / 1000);

        process();

        gettimeofday(&time_now, nullptr);
        time_t new_time = (time_now.tv_usec / 1000);

        time_t rest = new_time - time;
        std::this_thread::sleep_for(std::chrono::milliseconds(rate - rest));
    }
}

void ThGameEvents::stop(){
    is_running = false;
}

void ThGameEvents::add(Event* event){
    events.push_back(event);
}

void ThGameEvents::process(){
    for (int i = 0; i < (int)events.size(); ++i){
        events[i]->process(_game_model_queue);
        if (events[i]->finished()){ 
            delete(events[i]);
            events.erase(i); 
            --i;
        }
    }
}

ThGameEvents::~ThGameEvents(){
    for (int i = 0; i < (int)events.size(); ++i){
        delete(events[i]);
    }
}

