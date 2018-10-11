//
// Created by cherdakov on 09.10.18.
//

#include "InputParser.h"
#include <algorithm>
InputParser::InputParser(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        this->tokens.emplace_back(argv[i]);
    }
}

const std::string &InputParser::getOption(const std::string &option) const {
    auto it = std::find(this->tokens.begin(), this->tokens.end(), option);
    if (it != this->tokens.end() && ++it != this->tokens.end()) {
        return *it;
    }
    static const std::string empty_string;
    return empty_string;
}

bool InputParser::optionExists(const std::string &option) const {
    return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
}
