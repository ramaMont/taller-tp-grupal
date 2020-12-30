#ifndef __P_R_SERVER__
#define __P_R_SERVER__

#include <vector>
#include <string>
#include <map>

extern std::map<int, float> configs;

enum CONFIG{
	minutos_partida = 0,
	vida_maxima,
	vida_minima,
	cantidad_de_vidas,
	balas_iniciales,
	balas_maximas,
	segundos_cerrar_puerta,
	precision_pistola,
	precision_ametralladora,
	precision_canion,
	balas_rafaga_ametralladora,
	balas_gastadas_lanzacohetes,
	distancia_explosion_cohete,
	rango_de_disparo,
	baja_precision_distancia,
	maximo_danio,
	frecuencia_ametralladora,
	frecuencia_canion,
	puntos_comida,
	puntos_kit,
	cantidad_balas,
	puntos_cruz,
	puntos_copa,
	puntos_cofre,
	puntos_corona
};

class ParamReaderServer{
private:
    std::vector<std::string> args;
public:
    explicit ParamReaderServer(int argc, char** argv);
    void getConfiguration();
    std::string getPort();
    ~ParamReaderServer();
};

#endif
