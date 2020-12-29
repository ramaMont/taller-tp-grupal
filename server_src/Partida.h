#ifndef __PARTIDA__
#define __PARTIDA__

#include <string>
#include <vector>

#include <map>
#include <ctime>
#include <Player.h>
#include <Mapa.h>
#include <yaml-cpp/yaml.h>
//>>>>>>> origin/main

class Partida{
private:
    std::string params;
/*<<<<<<< HEAD*/
    std::map<std::string, Player*> jugadores;
    std::vector<Player*> bots;
    time_t tiempo_inicial;
/*=======
    std::vector<Player *> jugadores;*/
//>>>>>>> origin/main
public:
    explicit Partida(const std::string& params);
    void run();
    bool agregarJugador(const std::string& nombre);
    void agregarRobot();
    void comenzarPartida();
    void iniciarMapa(Mapa& mapa, YAML::Node elementos);
    void recibirEventos();
    bool todosMuertos();
    void mostrarGanadores();
    void mayoresPuntajes(std::string& buffer, size_t (Player::*funcion)());
    ~Partida();
};

#endif
