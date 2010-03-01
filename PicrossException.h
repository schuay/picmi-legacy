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
