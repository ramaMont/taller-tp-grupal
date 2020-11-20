#include "ParamReaderServer.h"

ParamReaderServer::ParamReaderServer(int argc, char** argv): 
    args(argv, argv+argc){
        if (argc != 3) throw -1;
}

ParamReaderServer::~ParamReaderServer(){
}
