#include "ParamReaderServer.h"

ParamReaderServer::ParamReaderServer(int argc, char** argv): 
    args(argv, argv+argc){
        if (argc != 3) throw -1;
}

std::string ParamReaderServer::getPort(){
    return args.at(1);
}

ParamReaderServer::~ParamReaderServer(){
}
