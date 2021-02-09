#ifndef __EXCEPTION_SERVER_H__
#define __EXCEPTION_SERVER_H__

#include <typeinfo>
#include <exception>
#include <string>


class ParamReaderException: public std::exception {
    std::string msg;
 public:
    explicit ParamReaderException(const std::string& error)
            : msg(error) {}
    virtual const char* what() const throw() {
        return msg.c_str();
    }
};


#endif
