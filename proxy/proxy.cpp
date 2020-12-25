#include "proxy.h"


#include <iostream>
#include <exception>
#include <vector>
#include <map>

#include <Protocol.h>
#include <Direccion.h>

// #include <ray_casting.h>
// #include <window.h>
// #include <texture.h>
#include <Mapa.h>

#include <Player.h>
#include <Posicionable.h>

#include <GameModel.h>
#include <ThUser.h>
#include <ThKeyReader.h>
//#include <ThDrawer.h>

// void draw(Window& window, Raycasting& ray_casting){
//   window.set_no_color();
//   ray_casting.calculate_ray_casting();
//   window.render();   
// }

void initMap(Mapa& map_server, Mapa& map_client, Player& player_server, Player& player_client){
    std::vector<std::vector<int>> a_map{
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    for(int i=0; i<24; i++){
        for(int j=0; j<24; j++){
            if(a_map[i][j]!=0){
                Coordinates position((float)i,(float)j);
                Posicionable* posicionable_server = new Posicionable(position);
                Posicionable* posicionable_client = new Posicionable(position);
                map_server.agregarPosicionable(posicionable_server,position);
                map_client.agregarPosicionable(posicionable_client,position);
            }
        }
    }
}

int run(){
    // int id = 0;
    // Mapa map_server(24, 24);
    // Mapa map_client(24,24);
    // Coordinates initial_position(2.5, 2.5);
    // Coordinates initial_direction(0, 1);
    // Player player_server(initial_position, initial_direction, map_server, id);
    // Player player_client(initial_position, initial_direction, map_client, id);
    // initMap(map_server, map_client, player_server, player_client);

    // std::map<int,Player *> players_server;
    // std::map<int,Player *> players_client;
    // std::map<int,ThSender *> users_sender;

    // ThDrawer th_drawer(player_client, map_client);

    // GameModelServer game_model_server(map_client, players_server, users_sender);
    // GameModelClient game_model_client(map_server, players_client);

    // ThReceiver th_receiver_server(game_model_server);
    // ThReceiver th_receiver_client(game_model_client);

    // ThSender th_sender_server(th_receiver_client, 0);
    // ThSender th_sender_client(th_receiver_server, 0);

    // ThUser th_user_server(0, th_receiver_server, th_sender_server);
    // ThUser th_user_client(0, th_receiver_client, th_sender_client);

    // game_model_server.addPlayer(&player_server);
    // game_model_client.addPlayer(&player_client);

    // game_model_server.addThSender(&th_sender_server);

    // ThKeyReader th_key_reader(th_sender_client);

    // th_key_reader.start();          // Lectura de teclas
    // while(true){
    //     th_drawer.run();            // Dibujo de juego en cliente
    //     th_user_client.run();       // Paso de mensaje a el th_sender_client
    //     th_sender_client.run();     // paso de protocolo al th_receiver_server
    //     th_receiver_server.run();   // paso de protocolo al game_model_server
    //     game_model_server.run();    // Procesamiento de instruccion
    //     th_sender_server.run();     // paso de protocolo al th_receiver_client
    //     th_receiver_client.run();   // paso de protocolo al game_model_client
    //     game_model_client.run();    // Procesamiento de instruccion y dibujo en pantalla.
    // }
    return 0;
}
