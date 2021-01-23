#ifndef __EVENT_H__
#define __EVENT_H__

#include <ctime>
#include "Objeto.h"
class ThGameEvents;
class ThGameModelServer;

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


class OpenEvent{
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
    public:
    FinishGameEvent();
    virtual void process(BlockingQueue<Protocol>& game_model_queue) override;
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
    Rocket* rocket;

    public:
    RocketEvent(Rocket* rocket);
    virtual void process(BlockingQueue<Protocol>& game_model_queue) override;
    ~RocketEvent();
};

#endif
