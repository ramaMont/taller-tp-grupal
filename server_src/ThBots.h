#ifndef __TH_BOTS_H__
#define __TH_BOTS_H__

#include <Thread.h>
#include <BlockingQueue.h>
#include <Protocol.h>
class ThGameModelServer;
#include <Bot.h>

#include <map>

class ThBots : public Thread{
    private:
    std::map<int, Bot*> bots;
    std::map<int, Player*>& players;
    BlockingQueue<Protocol>& _game_model_queue;
    int number_of_bots;
    ThGameModelServer* th_game_model;
    const Mapa& map;

    // Envia el protocolo del evento
    void makeEvent(int player_id, Bot::Event event);
    
    public:
    explicit ThBots(ThGameModelServer* th_game_model,
                    BlockingQueue<Protocol>& game_model_queue,
                    std::map<int,Player*>& players,
                    const Mapa& map,
                    int number_of_bots);
    
    // Procesa los bots y sus eventos
    virtual void run() override;
    
    // Agrega los bots y sus correspondientes jugadores
    void addBots();
    
    // Para el hilo
    virtual void stop() override;
    ~ThBots();
};

#endif
