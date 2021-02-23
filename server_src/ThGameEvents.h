#ifndef __TH_GAME_EVENTS_H__
#define __TH_GAME_EVENTS_H__

#include <Thread.h>
#include <BlockingQueue.h>
#include <Protocol.h>
class Event;
#include "Event.h"
#include "ProtectedVector.h"

class ThGameEvents : public Thread{
    private:
    ProtectedVector<Event*> events;
    BlockingQueue<Protocol>& _game_model_queue;
    
    public:
    explicit ThGameEvents(BlockingQueue<Protocol>& game_model_queue);
    
    // Procesa los eventos
    virtual void run() override;
    
    // Para el hilo
    virtual void stop() override;
    
    // Agrega el evento a la lista de eventos
    void add(Event* event);
    
    // Procesa cada evento de la lista de eventos
    void process();
    ~ThGameEvents();
};

#endif
