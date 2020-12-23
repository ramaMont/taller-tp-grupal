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
    while (!done) {
        while (SDL_PollEvent(&event)){
            switch (event.type) {
                case SDL_KEYDOWN: {
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                    switch (keyEvent.keysym.sym){
                        case SDLK_LEFT:
                            protocol.moveInDirection(
                                Protocol::direction::LEFT);
                            th_sender.push(protocol);
                            break;
                        case SDLK_RIGHT:
                            protocol.moveInDirection(
                                Protocol::direction::RIGHT);
                            th_sender.push(protocol);
                            break;
                        case SDLK_UP:
                            protocol.moveInDirection(
                                Protocol::direction::FORWARD);
                            th_sender.push(protocol);
                            break;
                        case SDLK_DOWN:
                            protocol.moveInDirection(
                                Protocol::direction::BACKWARD);
                            th_sender.push(protocol);
                            break;
                        case SDLK_q:
                            protocol.moveInDirection(
                                Protocol::direction::ROTATE_LEFT);
                            th_sender.push(protocol);
                            break;
                        case SDLK_e:
                            protocol.moveInDirection(
                                Protocol::direction::ROTATE_RIGHT);
                            th_sender.push(protocol);
                            break;
                    }
                }
                break;            
                case SDL_QUIT: {
                    done = SDL_TRUE;
                    stop();
                }
            }
        }
    }
}

void ThKeyReader::stop(){
    is_running = false;
}

ThKeyReader::~ThKeyReader(){
}
