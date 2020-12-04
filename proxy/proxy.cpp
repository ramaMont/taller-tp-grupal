#include "proxy.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
    int id = 0;
    Mapa map_server(24, 24);
    Mapa map_client(24,24);
    Coordinates initial_position(2.5, 2.5);
    Coordinates initial_direction(0, 1);
    Player player_server(initial_position, initial_direction, map_server, id);
    Player player_client(initial_position, initial_direction, map_client, id);
    initMap(map_server, map_client, player_server, player_client);

    GameModel game_model_server(std::move(map_client));
    GameModel game_model_client(std::move(map_server));

    ThReceiver th_receiver_server(game_model_server);
    ThReceiver th_receiver_client(game_model_client);

    ThSender th_sender_server(th_receiver_client, 0);
    ThSender th_sender_client(th_receiver_server, 0);

    ThUser th_user_server(0, th_receiver_server, th_sender_server);
    ThUser th_user_client(0, th_receiver_client, th_sender_client);

    game_model_server.addPlayer(&player_server);
    game_model_client.addPlayer(&player_client);

    game_model_server.addThSender(&th_sender_server);
    game_model_client.addThSender(&th_sender_client);

    while(true){
        th_user_client.run();     // Lectura de teclas y paso de mensaje a el th_sender_client
        th_sender_client.run(); // paso de protocolo al th_receiver_server
        th_receiver_server.run(); // paso de protocolo al game_model_server
        game_model_server.run();  // Procesamiento de instruccion
        th_sender_server.run(); // paso de protocolo al th_receiver_client
        th_receiver_client.run(); // paso de protocolo al game_model_client
        game_model_client.run();  // Procesamiento de instruccion y dibujo en pantalla.
    }


    // game_model_server.addUser(&thUserServer);
    // game_model_client.addUser(&thUserClient);
    // game_model_server.addPlayer(&player_server);
    // game_model_client.addPlayer(&player_client);

//    Window window(640,480);
//    Raycasting ray_casting(player_client, map,window);

//    draw(window, ray_casting);


//     SDL_bool done = SDL_FALSE;
//     while (!done) {
//       SDL_Event event;
//       while (SDL_PollEvent(&event)) {
//         switch(event.type) {
//           case SDL_KEYDOWN: {
//             SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
//             switch (keyEvent.keysym.sym) {
//               case SDLK_LEFT:
//                 // protocol.direction = LEFT;
//                 // protocol.id = 1;
//                 break;
//               case SDLK_RIGHT:
//                 // protocol.direction = RIGHT;
//                 // protocol.id = 1;
//                 break;
//               case SDLK_UP:
//                 // protocol.direction = FORWARD;
//                 // protocol.id = 1;
//                 break;
//               case SDLK_DOWN:
//                 // protocol.direction = BACKWARD;
//                 // protocol.id = 1;
//                 break;
//               case SDLK_q:
//                 // protocol.direction = ROTATE_LEFT;
//                 // protocol.id = 1;
//                 break;
//               case SDLK_e:
//                 // protocol.direction = ROTATE_RIGHT;
//                 // protocol.id = 1;
//                 break;
//             }
//           } // Fin KEY_DOWN
//           break;            
//           case SDL_QUIT: {
//             done = SDL_TRUE;
//           }
//         }
//         //server.setProtocol(protocol);
//         //protocol = server.reciveProtocol();
//         //updateModel();
//         // std::cout << protocol.direction << std::endl;
// //        std::cout << sizeof(protocol) << std::endl;
// //        draw(window, ray_casting);
//       }
//     }
    return 0;
}
