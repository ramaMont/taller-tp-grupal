#ifndef __CLIENT__HOLDER__
#define __CLIENT__HOLDER__

#include <string>
#include <utility>
#include <vector>

#include <Protocol.h>
#include <Socket.h>
class ThReceiverClient;
#include "ThReceiverClient.h"
#include "GameModelClient.h"

class ClientHolder{
private:
    std::string _host_dns;
    std::string _port;
    int user_id;
    SocketClient* socket;
    GameModelClient* _game_model;
    ThReceiverClient* _cl_th_receiver;
    ThSender* _th_sender;
    std::string _map_filename;
    bool ready_to_play;
    int _game_id;
    int _map_id_checksum;
    UserClient* _user_client;
    int resolution_width;
    int resolution_height;
    bool fullscreen;

    //Informacion del fin de juego
    int _winner_id;
    bool game_done;
    std::vector<std::pair<int,int>> _ordered_players_kills;
    std::vector<std::pair<int,int>> _ordered_players_points;
    std::vector<std::pair<int,int>> _ordered_players_bullets;    
    bool player_alive;

    void setGameConfig(std::string& resolution, bool _fullscreen);
    void setId(Protocol& protocol);
    void processReception(Protocol& protocol);
    void createGameModel(std::string map_filename, int id_user_protocol,
        int game_id);
    void addLoggedUsers();
    void logginScreen();
    void receiveConfiguration();

public:
    ClientHolder();
    void run();
    void crearPartida(const std::string& map_filename, 
        int bots_cty, int& game_id, std::string& resolution,
        bool fullscreen);
    void unirseAPartida(const std::string& id_partida, std::string& resolution,
                        bool fullscreen);
    void logged(const std::string& puerto, const std::string& servidor,
        int& user_id);
    // Se cierra todo lo correspondiente a qt y se setea en true el 
    // booleano ready to play
    void startGame();
    void launchGame();
    void connectionLost();
    ~ClientHolder();
};

#endif
