/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef PICROSSEXCEPTION_H
#define PICROSSEXCEPTION_H

#include <exception>
#include <string>

class PicException : public std::exception
{
public:
    PicException();
    PicException(std::string message);
    ~PicException() throw();

    const char* what() const throw();
private:
    std::string Message;
};

#endif // PICROSSEXCEPTION_H
