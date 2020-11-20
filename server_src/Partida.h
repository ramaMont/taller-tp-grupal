#ifndef __PARTIDA__
#define __PARTIDA__

#include <string>
#include <vector>
#include "Jugador.h"

class Partida{
private:
    std::string params;
    std::vector<Jugador *> jugadores;
public:
    explicit Partida(std::string params);
    void run();
    ~Partida();
};

#endif
