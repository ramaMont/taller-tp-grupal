#ifndef __SERVER__HOLDER__
#define __SERVER_HOLDER__

#include "ParamReaderServer.h"

class ServerHolder{
private:
    ParamReaderServer paramReader;
public:
    ServerHolder(int argc, char** argv);
    void run();
    ~ServerHolder();
};

#endif
