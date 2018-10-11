//
// Created by cherdakov on 09.10.18.
//

#ifndef INC_2GIS_ILLEGALARGUMENTSEXCEPTION_H
#define INC_2GIS_ILLEGALARGUMENTSEXCEPTION_H

#include "exception"
#include "string"



class IllegalArgumentsException : public std::exception {
private:
    std::string message;
public:
    explicit IllegalArgumentsException(std::string message);
    const std::string& getMessage() const;
    const char* what();
};

#endif //INC_2GIS_ILLEGALARGUMENTSEXCEPTION_H
