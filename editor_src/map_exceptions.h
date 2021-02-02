#ifndef EDITOR_H
#define EDITOR_H

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

#endif // EDITOR_H
