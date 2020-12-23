#ifndef __PARTIDA__
#define __PARTIDA__

#include <string>
#include <vector>
#include <Player.h>

class Partida{
private:
    std::string params;
    std::vector<Player *> jugadores;
public:
    explicit Partida(const std::string& params);
    void run();
    ~Partida();
};

#endif
