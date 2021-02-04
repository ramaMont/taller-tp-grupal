#ifndef MAP_EXCEPTION_H
#define MAP_EXCEPTION_H

#include <exception>
#include <string>

class MapException: public std::exception {
    std::string msg;
 public:
    explicit MapException(const std::string& error)
            : msg(error) {}
    virtual const char* what() const throw() {
        return msg.c_str();
    }
};

#endif // MAP_EXCEPTION_H
