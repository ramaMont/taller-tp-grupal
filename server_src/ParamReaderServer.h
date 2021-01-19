#ifndef __P_R_SERVER__
#define __P_R_SERVER__

#include <vector>
#include <string>

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
