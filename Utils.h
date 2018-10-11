#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by cherdakov on 09.10.18.
//

#ifndef INC_2GIS_UTILS_H
#define INC_2GIS_UTILS_H

#include <string>
#include <fstream>
#include <vector>
#include <tuple>
#include <unordered_map>
#include "InputParser.h"
#include "IllegalArgumentsException.h"

const std::string REQUIRED_OPTIONS_NOT_FOUND = "Required options not found, use -h option for details";
const std::string FILENAME_OPTION_NOT_FOUND = "Option -f does not exists";
const std::string CHECKSUM_MODE = "checksum";
const std::string HELP_MODE = "help";
const std::string WORDS_MODE = "words";
const std::string OPTION_V_NOT_FOUND = "Option -v is Required for this mode";
const std::string EMPTY_WORD = "Word is empty";
const std::string INCORRECT_MODE = "Incorrect mode";
const std::string HELP_OPTION = "-h";
const std::string MODE_OPTION = "-m";
const std::string FILENAME_OPTION = "-f";
const std::string WORD_OPTION = "-v";

class Utils {
public:
    static uint32_t getCountWordsInFile(const std::string &filename, const std::string &word);

    static uint32_t getFileCheckSum(const std::string &filename);

    static std::tuple<std::string, std::string, std::string> parseArguments(const InputParser &inputParser);
};


#endif //INC_2GIS_UTILS_H

#pragma clang diagnostic pop