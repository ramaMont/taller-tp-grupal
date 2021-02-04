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
    std::string _map_filename;
    bool ready_to_play;
    int _game_id;
    int _map_id_checksum;
    UserClient* _user_client;

    //Informacion del fin de juego
    int _winner_id;
    bool game_done;
    std::vector<std::pair<int,int>> _ordered_players_kills;
    std::vector<std::pair<int,int>> _ordered_players_points;
    std::vector<std::pair<int,int>> _ordered_players_bullets;    
    
    void setId(Protocol& protocol);
    void processReception(Protocol& protocol);
    void createGameModel(std::string map_filename, int id_user_protocol, int game_id);
    void addLoggedUsers();
    void logginScreen();
    void receiveConfiguration();
public:
    ClientHolder();
    void run();
    void crearPartida(const std::string& map_filename, 
        int bots_cty, int& game_id);
    void unirseAPartida(std::string& id_partida);
    void logged(std::string& nombre, std::string& puerto, std::string& servidor);
    // Se cierra todo lo correspondiente a qt y se setea en true el booleano ready to play
    void startGame();
    void launchGame();
    void connectionLost();
    ~ClientHolder();
};

#endif
