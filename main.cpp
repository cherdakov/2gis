//
// Created by cherdakov on 08.10.18.
//

#include <string>
#include <iostream>
#include <vector>
#include <cctype>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include <utility>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "InputParser.h"
#include "IllegalArgumentsException.h"
#include "Utils.h"


int main(int argc, char **argv) {
    InputParser inputParser(argc, argv);
    try {
        //TODO:replace with decomposition
        std::string mode, filename, word;
        std::tie(mode, filename, word) = Utils::parseArguments(inputParser);
        if (HELP_MODE == mode) {
            std::cout << REQUIRED_OPTIONS_NOT_FOUND << std::endl;
        } else if (CHECKSUM_MODE == mode) {
            auto checkSum = Utils::getFileCheckSum(filename);
            std::cout << "checkSum:" << checkSum << std::endl;
        } else if (WORDS_MODE == mode) {
            auto count = Utils::getCountWordsInFile(filename, word);
            std::cout << "count:" << count << std::endl;
        }
    } catch (IllegalArgumentsException &e) {
        std::cout << e.getMessage() << std::endl;
    } catch (std::ifstream::failure &e) {
        std::cout << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}