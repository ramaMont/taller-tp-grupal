#include "ParamReaderServer.h"

#include <yaml-cpp/yaml.h>
#include <string>

std::map<std::string, float> configuracion;

ParamReaderServer::ParamReaderServer(int argc, char** argv): 
    args(argv, argv+argc){
        if (argc != 3) throw -1;
    std::string ruta_config = "../../server_src/";
    YAML::Node config = YAML::LoadFile(ruta_config.append(argv[1]));
	configuracion =
	 std::move(config.as<std::map<std::string, float>>());
}

ParamReaderServer::~ParamReaderServer(){
}
