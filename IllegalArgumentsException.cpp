//
// Created by cherdakov on 09.10.18.
//

#include "IllegalArgumentsException.h"

IllegalArgumentsException::IllegalArgumentsException(std::string message) : message(std::move(message)) {}

const std::string& IllegalArgumentsException::getMessage() const {
    return message;
}

const char *IllegalArgumentsException::what() {
    return "IllegalArgumentsException";
}