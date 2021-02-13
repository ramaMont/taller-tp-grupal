#include "ParamReaderServer.h"

#include <ConfigVariable.h>
#include "ExceptionServer.h"

#include <yaml-cpp/yaml.h>
#include <string>
#include <iostream>

std::map<int, float> configs;


ParamReaderServer::ParamReaderServer(int argc, char** argv): 
    args(argv, argv+argc){
        if (argc != 3) 
			throw ParamReaderException("Cantidad de parametros incorrecta\n");
    getConfiguration();
}

void ParamReaderServer::getConfiguration(){
	const std::string RUTA_CONFIG = "../data/";
	YAML::Node config;
	try{
		config = YAML::LoadFile(RUTA_CONFIG + args.at(2));
	} catch (std::exception& e) {
		std::string error = e.what();
		throw ParamReaderException(error + "\n");
	}

	configs[CONFIG::minutos_partida] = 
	    config["minutos_partida"].as<int>();
	configs[CONFIG::vida_maxima] = 
	    config["vida_maxima"].as<int>();
	configs[CONFIG::vida_minima] = 
	    config["vida_minima"].as<int>();
	configs[CONFIG::cantidad_de_vidas] = 
	    config["cantidad_de_vidas"].as<int>();
	configs[CONFIG::balas_iniciales] = 
	    config["balas_iniciales"].as<int>();
	configs[CONFIG::balas_maximas] = 
	    config["balas_maximas"].as<int>();
	configs[CONFIG::segundos_cerrar_puerta] = 
	    config["segundos_cerrar_puerta"].as<int>();
	configs[CONFIG::open_distance] = 
	    config["open_distance"].as<float>();
	configs[CONFIG::precision_pistola] = 
	    config["precision_pistola"].as<float>();
	configs[CONFIG::precision_ametralladora] = 
	    config["precision_ametralladora"].as<float>();
	configs[CONFIG::precision_canion] = 
	    config["precision_canion"].as<float>();
	configs[CONFIG::balas_rafaga_ametralladora] = 
	    config["balas_por_rafaga_ametralladora"].as<int>();
	configs[CONFIG::balas_gastadas_lanzacohetes] = 
	    config["balas_gastadas_lanzacohetes"].as<int>();
	configs[CONFIG::distancia_explosion_cohete] = 
	    config["distancia_explosion_cohete"].as<float>();
	configs[CONFIG::rango_de_disparo] = 
	    config["rango_de_disparo"].as<float>();
	configs[CONFIG::baja_precision_distancia] = 
	    config["baja_de_precision_por_distancia"].as<float>();
	configs[CONFIG::maximo_danio] = 
	    config["maximo_danio"].as<int>();
	configs[CONFIG::frecuencia_ametralladora] = 
	    config["frecuencia_rafaga_ametralladora"].as<float>();
	configs[CONFIG::frecuencia_canion] = 
	    config["frecuencia_disparo_canion"].as<float>();
	configs[CONFIG::puntos_comida] = 
	    config["puntos_comida"].as<int>();
	configs[CONFIG::puntos_kit] = 
	    config["puntos_kit"].as<int>();
	configs[CONFIG::cantidad_balas] = 
	    config["cantidad_balas"].as<int>();
	configs[CONFIG::puntos_cruz] = 
	    config["puntos_cruz"].as<int>();
	configs[CONFIG::puntos_copa] = 
	    config["puntos_copa"].as<int>();
	configs[CONFIG::puntos_cofre] = 
	    config["puntos_cofre"].as<int>();
	configs[CONFIG::puntos_corona] = 
	    config["puntos_corona"].as<int>();
}

std::string ParamReaderServer::getPort(){
    return args.at(1);
}

ParamReaderServer::~ParamReaderServer(){
}
