#ifndef __EVENT_H__
#define __EVENT_H__

#include <ctime>
#include "Object.h"
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


class FinishGameEvent: public Event{
    public:
    FinishGameEvent();
    virtual void process(BlockingQueue<Protocol>& game_model_queue) override;
    ~FinishGameEvent();
};

class DoorOpeningEvent: public Event{
    private:
    Door* door;

    public:
    explicit DoorOpeningEvent(Door *door);
    virtual void process(BlockingQueue<Protocol>& game_model_queue) override;
    ~DoorOpeningEvent();
};

class DoorEvent: public Event{
    private:
    Door* door;
    std::atomic<bool>& reopen;

    public:
    explicit DoorEvent(Door *door);
    virtual void process(BlockingQueue<Protocol>& game_model_queue) override;
    void resetTime();
    ~DoorEvent();
};


class RocketEvent: public Event{
    private:
    Rocket* rocket;
    Coordinates rocket_pos;
    Coordinates rocket_dir;
    int rocket_id;
    std::atomic<bool> _exploded;

    public:
    explicit RocketEvent(Rocket* rocket);
    virtual void process(BlockingQueue<Protocol>& game_model_queue) override;
    ~RocketEvent();
};

#endif
