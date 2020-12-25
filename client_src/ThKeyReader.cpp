#include "ThKeyReader.h"

#include <Protocol.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

ThKeyReader::ThKeyReader(ThSender& th_sender):
        Thread(), th_sender(th_sender){
}

void ThKeyReader::run(){
    SDL_bool done = SDL_FALSE;
    int id = th_sender.getId();
    Protocol protocol(id);
    SDL_Event event;
    const Uint8 *keys = SDL_GetKeyboardState(NULL);    
    while (!done) {


        if(keys[SDL_SCANCODE_RIGHT]){
            protocol.moveInDirection(
                Protocol::direction::RIGHT);
            th_sender.push(protocol);
        }
        if(keys[SDL_SCANCODE_LEFT]){
            protocol.moveInDirection(
                Protocol::direction::ROTATE_LEFT);
            th_sender.push(protocol);
        }
        if(keys[SDL_SCANCODE_UP]){
            protocol.moveInDirection(
                Protocol::direction::FORWARD);
            th_sender.push(protocol);
        }
        if(keys[SDL_SCANCODE_DOWN]){
            protocol.moveInDirection(
                Protocol::direction::BACKWARD);
            th_sender.push(protocol);
        }

        while (SDL_PollEvent(&event)) { 

          switch(event.type) {
            case SDL_QUIT: {
              done = SDL_TRUE;
            }
          }
        }
        SDL_Delay(20);
    }
}

void ThKeyReader::stop(){
    is_running = false;
}

ThKeyReader::~ThKeyReader(){
}
