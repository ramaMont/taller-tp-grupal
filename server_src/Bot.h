#ifndef __BOT_H__
#define __BOT_H__

class ServerMap;
class Player;
#include <map>

extern "C"{
	#include "lua/include/lua.h"
	#include "lua/include/lauxlib.h"
	#include "lua/include/lualib.h"
}

class Bot{
	private:
	lua_State* script;
	const ServerMap& map;
	
	public:
        enum Event{
		MoveForward = 0,
		RotateLeft,
		RotateRight,
		Shoot,
		SwitchToKnife,
		OpenDoor,
		Nothing
        };

    explicit Bot(const ServerMap& map);
    
    // Invoca la funcion para cargar el mapa en el script de lua
    void loadMap();
    
    // Dado el jugador correspondiente al bot y la lista de jugadores
    // Retorna el evento producido por el bot
    Bot::Event getEvent(Player* player, std::map<int, Player*>& enemies);
    
    // Carga en el script de lua el numero que representa el objeto del mapa
    static int luaGetMapObject(lua_State *L);
    
    // Carga en el script de lua la informacion correspondiente al jugador
    int pushInfoPlayer(Player* player);
    
    // Carga en el script de lua la informacion de los enemigos
    int pushInfoEnemies(Player* j, std::map<int, Player*>& enemies);
    ~Bot();
};

#endif
