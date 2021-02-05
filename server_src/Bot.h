#ifndef __BOT_H__
#define __BOT_H__

class Mapa;
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
	const Mapa& map;
	
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

    Bot(const Mapa& map);
    void loadMap();
    Bot::Event getEvent(Player* player, std::map<int, Player*>& enemies);
    static int luaGetMapObject(lua_State *L);
    int pushInfoPlayer(Player* player);
    int pushInfoEnemies(Player* j, std::map<int, Player*>& enemies);
    ~Bot();
};

#endif
