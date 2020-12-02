#ifndef __PARTIDA__
#define __PARTIDA__

#include <string>
#include <vector>
#include <map>
#include <ctime>
#include <Jugador.h>
#include <Mapa.h>


class Partida{
private:
    std::string params;
    std::map<std::string, Jugador *> jugadores;
    std::vector<Jugador *> robots;
    time_t tiempo_inicial;
public:
    explicit Partida(const std::string& params);
    void run();
    bool agregarJugador(const std::string& nombre);
    void agregarRobot();
    void comenzarPartida();
    void iniciarMapa(Mapa& mapa);
    void recibirEventos();
    bool todosMuertos();
    void mostrarGanadores();
    void mayoresEnemigosMatados(std::string& buffer);
    void mayorPuntuacion(std::string& buffer);
    void mayoresBalasDisparadas(std::string& buffer);
    ~Partida();
};

#endif
