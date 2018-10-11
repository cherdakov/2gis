//
// Created by cherdakov on 09.10.18.
//

#ifndef INC_2GIS_INPUTPARSER_H
#define INC_2GIS_INPUTPARSER_H

#include <string>
#include <vector>
class InputParser {
public:
    InputParser(int argc, char **argv);
    const std::string& getOption(const std::string& option) const ;
    bool optionExists(const std::string &option) const ;
private:
    std::vector<std::string> tokens;
};

#endif //INC_2GIS_INPUTPARSER_H
