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

const std::string CHECKSUM_MODE = "checksum";
const std::string HELP_MODE = "help";
const std::string WORDS_MODE = "words";
const std::string EMPTY_WORD = "Word is empty";
const std::string INCORRECT_MODE = "Incorrect mode";
const std::string HELP_OPTION = "-h";
const std::string MODE_OPTION = "-m";
const std::string FILENAME_OPTION = "-f";
const std::string WORD_OPTION = "-v";
const std::string REQUIRED_OPTIONS_NOT_FOUND =
        std::string("Required options not found, use ") + HELP_OPTION + " option for details";
const std::string OPTION_V_NOT_FOUND = std::string("Option ") + WORD_OPTION + " is Required for this mode";
const std::string FILENAME_OPTION_NOT_FOUND = std::string("Option ") + FILENAME_OPTION + " does not exists";
const std::string HELP_MESSAGE = std::string("usage:\n") +
                                 "2gis " +
                                 "[" + MODE_OPTION + " " + WORDS_MODE + "|" + CHECKSUM_MODE + "]" +
                                 "[" + FILENAME_OPTION + " " + "file]" +
                                 "[" + WORD_OPTION + " word, required for " + WORDS_MODE + " mode]\n" +
                                 "about modes:\n" +
                                 WORDS_MODE + ": counts the number of occurrences of the word in the text\n" +
                                 CHECKSUM_MODE + ": calculates the checksum of file\n";


class Utils {
public:
    static uint32_t getCountWordsInFile(const std::string &filename, const std::string &word);

    static uint32_t getFileCheckSum(const std::string &filename);

    static std::tuple<std::string, std::string, std::string> parseArguments(const InputParser &inputParser);
};


#endif //INC_2GIS_UTILS_H

#pragma clang diagnostic pop