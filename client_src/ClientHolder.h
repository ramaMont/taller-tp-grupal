#ifndef __CLIENT__HOLDER__
#define __CLIENT__HOLDER__

#include <string>
#include <Protocol.h>

class ClientHolder{
private:
    std::string _player_name;
    std::string _host_dns;
    std::string _port;
    void setId(Protocol& protocol, int& id);
public:
    ClientHolder();
    void logginScreen();
    void run();
    ~ClientHolder();
};

#endif
