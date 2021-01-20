#ifndef __EXCEPTION_SERVER_H__
#define __EXCEPTION_SERVER_H__

#include <typeinfo>

class RocketException : public std::exception {
    public:
    explicit RocketException() noexcept {}
    virtual ~RocketException() noexcept {}
};

#endif
