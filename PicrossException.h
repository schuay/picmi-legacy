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

#include <string>
#include <exception>

class PicrossException : public std::exception
{
public:
    PicrossException();
    PicrossException(std::string message);
    ~PicrossException() throw();

    const char* what() const throw();
private:
    std::string Message;
};

#endif // PICROSSEXCEPTION_H
