/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "b_picexception.h"
namespace BoardGame {

Exception::Exception() { }
Exception::Exception(std::string message) {
    Message = message;
}

Exception::~Exception() throw() { }

const char* Exception::what() const throw() {
    return Message.c_str();
}
}
