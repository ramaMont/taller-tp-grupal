#include "ThGameEvents.h"


ThGameEvents::ThGameEvents(BlockingQueue<Protocol>& game_model_queue):
    Thread(), _game_model_queue(game_model_queue){
}

void ThGameEvents::run(){
    is_running = true;
    while (is_running){
        process();
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
        events[i]->process();
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

