#include "PicrossException.h"

PicrossException::PicrossException() { }
PicrossException::PicrossException(std::string message) {
    Message = message;
}

PicrossException::~PicrossException() throw() { }

const char* PicrossException::what() const throw() {
    return Message.c_str();
}
