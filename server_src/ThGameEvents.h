#ifndef __TH_GAME_EVENTS_H__
#define __TH_GAME_EVENTS_H__

#include <Thread.h>
#include <BlockingQueue.h>
#include <Protocol.h>
class Event;
#include <Event.h>
#include <ProtectedVector.h>

class ThGameEvents : public Thread{
    private:
    ProtectedVector<Event*> events;
    BlockingQueue<Protocol>& _game_model_queue;
    
    public:
    explicit ThGameEvents(BlockingQueue<Protocol>& game_model_queue);
    virtual void run() override;
    virtual void stop() override;
    void add(Event* event);
    void process();
    ~ThGameEvents();
};

#endif
