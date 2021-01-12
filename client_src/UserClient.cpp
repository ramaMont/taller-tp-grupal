#include "UserClient.h"

#include <iostream>
#include "Cl_Mapa.h"
#include <vector>
#include <map>
#include <GameModel.h>

#include <thread>
#include <chrono>
#include <iostream>
#include <sys/time.h>

#include <vector>
#include <utility>

UserClient::UserClient(int user_id, ClThReceiver& th_receiver,
        ThSender& th_sender):
    th_receiver(th_receiver), th_sender(th_sender),
    _th_game_model(nullptr), is_creator(false), user_id(user_id){
}

void UserClient::joinGame(int& game_id) {
    bool ready = false;
    Protocol protocol_response;
    while (!ready) {
        Protocol protocol(game_id);
        protocol.setAction(Protocol::action::JOIN_GAME);
        th_sender.push(protocol);
        protocol_response = operations.pop();
        processReception(protocol_response, ready);
    }

    ready = false;

    while (!ready) {
        protocol_response = operations.pop();
        processReception(protocol_response, ready);
    }

    protocol_response = operations.pop();
    processReception(protocol_response, ready);

    std::cout << "Esperando a iniciar la partida\n";
}

void UserClient::createGame(int& id_map) {
    bool ready = false;
    Protocol protocol_response;
    while (!ready){
        Protocol protocol(id_map);
        protocol.setAction(Protocol::action::CREATE_GAME);
        th_sender.push(protocol);
        is_creator = true;
        protocol_response = operations.pop();
        processReception(protocol_response, ready);
    }
    ready = false;

    while (!ready){
        protocol_response = operations.pop();
        processReception(protocol_response, ready);
    }

    if (!is_creator){
        protocol_response = operations.pop();
        processReception(protocol_response, ready);
    }
    std::cout << "Esperando a iniciar la partida\n";

}

void UserClient::joinOrCreateGame(){
    int option_input;
    bool ready = false;
    Protocol protocol_response;

    while (!ready){
        std::cout << "Introduzca 1 para crear partida\n";
        std::cout << "Introduzca 2 unirse a una partida\n";
        std::cin >> option_input;
        switch (option_input){
            case 1:{
                int id_map;
                std::cout << "Introduzca el ID del mapa\n";
                std::cin >> id_map;
                Protocol protocol(id_map);
                protocol.setAction(Protocol::action::CREATE_GAME);
                th_sender.push(protocol);
                is_creator = true;
                protocol_response = operations.pop();
                processReception(protocol_response, ready);
                break;
            }
            case 2:{
                int game_id;
                std::cout << "Introduzca el ID de la partida\n";
                std::cin >> game_id;
                Protocol protocol(game_id);
                protocol.setAction(Protocol::action::JOIN_GAME);
                th_sender.push(protocol);
                protocol_response = operations.pop();
                processReception(protocol_response, ready);
                break;
            }
            default:
                std::cout << "Opcion incorrecta, intente nuevamente\n";
                break;
        }
    }

    ready = false;

    while (!ready){
        protocol_response = operations.pop();
        processReception(protocol_response, ready);
    }

    if (!is_creator){
        protocol_response = operations.pop();
        processReception(protocol_response, ready);
    }
    std::cout << "Esperando a iniciar la partida\n";
}

void UserClient::waitForAction(Protocol::action desired_action){
    bool ready = false;
    while (!ready){
        Protocol protocol = operations.pop();
        if (protocol.getAction() == desired_action)
            ready = true;
    }
}

void UserClient::launchGame() {
    Protocol protocol(_th_game_model->getId());
    protocol.setAction(Protocol::action::LAUNCH_GAME);
    th_sender.push(protocol);
}

void UserClient::waitUntilLaunch(){
    int option_input;
    bool ready = false;
    while (!ready){
        std::cout << "Introduzca 1 para lanzar la partida\n";
        std::cin >> option_input;
        switch (option_input){
            case 1:{
                Protocol protocol(_th_game_model->getId());
                protocol.setAction(Protocol::action::LAUNCH_GAME);
                th_sender.push(protocol);
                ready = true;
                break;
            }
            default:
                std::cout << "Opcion no valida\n";
                break;
        }
    }
}

void UserClient::processReception(Protocol& protocol, bool& ready){
    switch (protocol.getAction()){
        case Protocol::action::OK:
            ready = true;
            break;
        case Protocol::action::CREATE_GAME:
            createGameModel(protocol.getMapId(), user_id, protocol.getGameId());
            std::cout << "Partida creada\nId de Partida: " << 
                protocol.getGameId() << std::endl;
            ready = true;
            break;
        case Protocol::action::ADD_PLAYER:{
            if (_th_game_model == nullptr){
                protocol.getUserId();
                createGameModel(protocol.getMapId(), protocol.getUserId(), 
                    protocol.getGameId());
            }
            else{
                _th_game_model->addPlayer(protocol.getUserId());
            }
            break;
        }
        case Protocol::action::END:
            ready = true;
            break;
        case Protocol::action::ERROR:
            // TODO: algo salio mal.
            std::cout << "Ha ocurrido un error, intente nuevamente\n";
            ready = false;
            break;
        default:
            std::cout << "Nunca deberia entrar acá\n";
            // TODO: algo salio muy mal.
            break;
    }
}

void UserClient::createGameModel(int map_id, int id_user_protocol, int game_id){
    _th_game_model = new GameModelClient(id_user_protocol, map_id, game_id, user_id);
    th_receiver.setGameModel(_th_game_model);
}

// Hacer todo para empezar a jugar la partida.
void UserClient::play(){
    waitForAction(Protocol::action::BEGIN);
    gameLoop();
}

void UserClient::run(){
    joinOrCreateGame();
    if (is_creator)
        waitUntilLaunch();
    play();
}

void UserClient::push(Protocol protocol){
    operations.push(protocol);
}

void UserClient::stop(){
    //TODO:Cerrar la cola bloqueante para que se destrabe del pop
    //is_running = false;
    operations.stop();
}

void UserClient::removePlayer(int user_id){
    if (_th_game_model != nullptr){
        _th_game_model->removePlayer(user_id);
    }
}

void UserClient::get_keys(const Uint8 *keys, SDL_Event &event, Protocol &protocol, SDL_bool &done,Jugador& jugador){
    if(keys[SDL_SCANCODE_RIGHT]){
        protocol.moveInDirection(
            Protocol::direction::ROTATE_RIGHT);
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

    if(keys[SDL_SCANCODE_RCTRL] or keys[SDL_SCANCODE_LCTRL]){
        if(jugador.can_shoot()){
            protocol.setAction(
                Protocol::action::SHOOT);
            th_sender.push(protocol);
        }
    }else{
        //player.stopped_shooting();
    }
    while (SDL_PollEvent(&event)) { 
        switch(event.type) {
            case SDL_QUIT: {
                done = SDL_TRUE;
            }
        }
    }
}

void UserClient::gameLoop(){
    SDL_bool done = SDL_FALSE;
    _th_game_model->showWindow();
    Screen screen(_th_game_model->getScreen());
    int id = th_sender.getId();
    Protocol protocol(id);
    SDL_Event event;

    time_t rate = 1000/30;

    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    time_t total_time = 0;
    time_t counter = 0;
    time_t max_time = 0;

    Jugador& jugador = _th_game_model->getPlayer();

    const Uint8 *keys = SDL_GetKeyboardState(NULL);    
    while (!done) {
        gettimeofday(&time_now, nullptr);
        time_t time = (time_now.tv_usec / 1000);

        get_keys(keys, event, protocol, done, jugador);

        _th_game_model->run();//Proceso los protocolos

        _th_game_model->updateFrameAnimations();

        screen.show();

        gettimeofday(&time_now, nullptr);
        time_t new_time = (time_now.tv_usec / 1000);

        time_t rest;
        if(new_time>time)
            rest = new_time - time;
        else
            rest = new_time - time + 1000;


        if(rest>max_time)
            max_time = rest;

        total_time+=rest;
        counter++;

        std::this_thread::sleep_for(std::chrono::milliseconds(rate - rest));
    }
    _th_game_model->hideWindow();
    std::cout<<"El maximo fue: "<<max_time<<std::endl;
    std::cout<<"El tiempo promedio fue:"<<total_time/counter<<std::endl;
}

UserClient::~UserClient(){
    if (_th_game_model != nullptr)
        delete(_th_game_model);
}
