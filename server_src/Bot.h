#ifndef __BOT_H__
#define __BOT_H__

//#include "Mapa.h"
class Mapa;
class Player;
//#include "Player.h"
#include <map>

extern "C"{
	#include "lua/include/lua.h"
	#include "lua/include/lauxlib.h"
	#include "lua/include/lualib.h"
}





class Bot{
	private:
	lua_State* script;
	const Mapa& mapa;
	
	public:
        enum Event{
		MoverAdelante = 0,
		MoverIzquierda,
		MoverDerecha,
		Disparar,
		CambiarArmaCuchillo,
		AbrirPuerta,
		Nada
        };
	
    Bot(const Mapa& mapa);
    void cargarMapa();
    Bot::Event getEvent(Player* jugador, std::map<int, Player*>& enemigos);
    static int luaObtenerObjetoMapa(lua_State *L);
    int pushInfoJugador(Player* jugador);
    int pushInfoEnemigos(Player* j, std::map<int, Player*>& enemigos);
    ~Bot();
};

#endif
