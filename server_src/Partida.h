#ifndef __PARTIDA__
#define __PARTIDA__

#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <Jugador.h>
#include <Mapa.h>
#include <yaml-cpp/yaml.h>


class Partida{
private:
    std::string params;
    std::map<std::string, Jugador *> jugadores;
    std::vector<Jugador *> bots;
    time_t tiempo_inicial;
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
    void mayoresPuntajes(std::string& buffer, size_t (Jugador::*funcion)());
    ~Partida();
};

#endif
