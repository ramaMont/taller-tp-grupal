#ifndef __CONFIG_VARIABLE__
#define __CONFIG_VARIABLE__

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

#endif
