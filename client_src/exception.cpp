#include "exception.h"

Exception::Exception(const char* message): error_message(message){}

const char* Exception::what()const noexcept {
    return error_message.c_str();
}
