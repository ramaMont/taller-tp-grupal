#ifndef __EVENT_H__
#define __EVENT_H__

#include <ctime>
#include "Objeto.h"
#include "ThGameModelServer.h"
class ThGameEvents;
#include "ThGameEvents.h"

class Event{
    protected:
    time_t _time;
    bool _finished;

    public:
    Event();
    virtual void process(BlockingQueue<Protocol>& game_model_queue) = 0;
    bool finished();
    virtual ~Event();
};


class OpenEvent: public Event{
    private:
    Player* player;
    Mapa& map;
    ThGameEvents& th_game_events;
    
    public:
    OpenEvent(Player* player, Mapa& map, ThGameEvents& game_e);
    void process(ThGameModelServer& game_model);
    ~OpenEvent();
};


class FinishGameEvent: public Event{
    private:
    std::map<int, Player*>& players;

    public:
    FinishGameEvent(std::map<int, Player*>& players);
    virtual void process(BlockingQueue<Protocol>& game_model_queue) override;
    bool someoneWon();
    ~FinishGameEvent();
};


class DoorEvent: public Event{
    private:
    Puerta* door;

    public:
    DoorEvent(Puerta *puerta);
    virtual void process(BlockingQueue<Protocol>& game_model_queue) override;
    ~DoorEvent();
};


class RocketEvent: public Event{
    private:
    Coordinates position;
    Coordinates direction;
    Player* player;
    std::map<int, Player*>& enemigos;
    Mapa& mapa;
    Objeto* object;

    public:
    RocketEvent(Coordinates position, Coordinates dir,
    Player* player, std::map<int, Player*>& enemigos);
    virtual void process(BlockingQueue<Protocol>& game_model_queue) override;
    void move();
    void explote();
    bool colisionaConObjeto(const Coordinates& inicio, const Coordinates& fin);
    ~RocketEvent();
};

#endif
