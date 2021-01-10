#ifndef __EVENT_H__
#define __EVENT_H__

#include <ctime>
#include "Objeto.h"

class Event{
    protected:
    time_t _time;
    bool _finished;

    public:
    Event();
    virtual void process() = 0;
    bool finished();
    virtual ~Event();
};


class DoorEvent: public Event{
    private:
    Puerta* door;

    public:
    DoorEvent(Puerta *puerta);
    virtual void process() override;
    ~DoorEvent();
};


class WallEvent: public Event{
    private:
    Coordinates position;
    Coordinates direction;
    ParedFalsa* object;
    Mapa& mapa;

    public:
    WallEvent(Coordinates position, Coordinates dir, 
        ParedFalsa* pared, Mapa& mapa);
    virtual void process() override;
    void move();
    ~WallEvent();
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
    virtual void process() override;
    void move();
    void explote();
    bool colisionaConObjeto(const Coordinates& inicio, const Coordinates& fin);
    ~RocketEvent();
};

#endif
