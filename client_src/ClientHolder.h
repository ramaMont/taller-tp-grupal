#ifndef __CLIENT__HOLDER__
#define __CLIENT__HOLDER__

#include <string>
#include <Protocol.h>
#include "Socket.h"

class ClientHolder{
private:
    std::string _player_name;
    std::string _host_dns;
    std::string _port;
    int id;
    SocketClient* socket;
    void setId(Protocol& protocol);
public:
    ClientHolder();
    void logginScreen();
    void run();
    void crearPartida(std::string& id_mapa);
    void unirseAPartida(std::string& id_partida);
    void logged(std::string& nombre, std::string& puerto, std::string& servidor);
    ~ClientHolder();
};

#endif
