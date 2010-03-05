/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "PicrossException.h"

PicrossException::PicrossException() { }
PicrossException::PicrossException(std::string message) {
    Message = message;
}

PicrossException::~PicrossException() throw() { }

const char* PicrossException::what() const throw() {
    return Message.c_str();
}
