#ifndef __CLIENT__HOLDER__
#define __CLIENT__HOLDER__

#include <string>
#include <Protocol.h>
#include "Socket.h"
class ClThReceiver;
#include "ClThReceiver.h"
#include "GameModelClient.h"

class ClientHolder{
private:
    std::string _player_name;
    std::string _host_dns;
    std::string _port;
    int user_id;
    SocketClient* socket;
    GameModelClient* _game_model;
    ClThReceiver* _cl_th_receiver;
    ThSender* _th_sender;
    void setId(Protocol& protocol);
    void processReception(Protocol& protocol);
    void createGameModel(int map_id, int id_user_protocol, int game_id);
    void addLoggedUsers();
    void logginScreen();
public:
    ClientHolder();
    void run();
    void crearPartida(const std::string& id_mapa, int& game_id);
    void unirseAPartida(std::string& id_partida);
    void logged(std::string& nombre, std::string& puerto, std::string& servidor);
    void startGame();
    void launchGame();
    ~ClientHolder();
};

#endif
