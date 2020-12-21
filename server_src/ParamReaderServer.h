#ifndef __P_R_SERVER__
#define __P_R_SERVER__

#include <vector>
#include <string>
#include <map>

extern std::map<std::string, float> configuracion;

class ParamReaderServer{
private:
    std::vector<std::string> args;
    std::vector<std::string> configs;
public:
    explicit ParamReaderServer(int argc, char** argv);
    ~ParamReaderServer();
};

#endif
