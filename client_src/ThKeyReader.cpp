#include "ThKeyReader.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

ThKeyReader::ThKeyReader(ThSender& th_sender):
        th_sender(th_sender){
}

void ThKeyReader::run(){
    SDL_bool done = SDL_FALSE;
    Protocol protocol(th_sender.getId());
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)){
            switch(event.type) {
                case SDL_KEYDOWN: {
                    SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
                    switch (keyEvent.keysym.sym) {
                        case SDLK_LEFT:
                            protocol.setDirection(LEFT);
                            break;
                        case SDLK_RIGHT:
                            protocol.setDirection(RIGHT);
                            break;
                        case SDLK_UP:
                            protocol.setDirection(FORWARD);
                            break;
                        case SDLK_DOWN:
                            protocol.setDirection(BACKWARD);
                            break;
                        case SDLK_q:
                            protocol.setDirection(ROTATE_LEFT);
                            break;
                        case SDLK_e:
                            protocol.setDirection(ROTATE_RIGHT);
                            break;
                    }        
                    th_sender.push(protocol);
                }
                break;            
                case SDL_QUIT: {
                    done = SDL_TRUE;
                }
            }

        }
    }
}

ThKeyReader::~ThKeyReader(){
}
