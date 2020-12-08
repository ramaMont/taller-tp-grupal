#ifndef __P_R_SERVER__
#define __P_R_SERVER__
#include <vector>
#include <string>

class ParamReaderServer{
private:
    std::vector<std::string> args;
    std::vector<std::string> configs;
public:
    explicit ParamReaderServer(int argc, char** argv);
    std::string getPort();
    ~ParamReaderServer();
};

#endif
