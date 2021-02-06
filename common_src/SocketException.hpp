#ifndef __SOCKET_EXCEPTION__
#define __SOCKET_EXCEPTION__

#include <exception>
#include <string>

class SocketException: public std::exception {
    std::string msg;
 public:
    explicit SocketException(const std::string& error)
            : msg(error) {}
    virtual const char* what() const throw() {
        return msg.c_str();
    }
};

#endif
