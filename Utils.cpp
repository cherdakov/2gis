//
// Created by cherdakov on 09.10.18.
//

#include "Utils.h"
#include <algorithm>


uint32_t Utils::getFileCheckSum(const std::string &filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        throw std::runtime_error("file not found");
    }
    const auto chunkSize = 16 * 1024;
    std::vector<uint32_t> buffer(chunkSize, 0);
    uint32_t hash = 0;
    while (fin.read(reinterpret_cast<char *>(buffer.data()), buffer.size())) {
        std::streamsize index = (fin.gcount() + 3) / 4; //division with rounding
        std::for_each(buffer.begin(), buffer.begin() + index, [&hash](uint32_t byte) { hash += byte; });
    }
    return hash;
}


std::tuple<std::string, std::string, std::string> Utils::parseArguments(const InputParser &inputParser) {
    std::string mode, filename, word;
    if (inputParser.optionExists(HELP_OPTION)) {
        mode = HELP_MODE;
        return std::make_tuple(mode, filename, word);
    }
    if (inputParser.optionExists(MODE_OPTION)) {
        mode = inputParser.getOption(MODE_OPTION);
    } else {
        throw IllegalArgumentsException(REQUIRED_OPTIONS_NOT_FOUND);
    }
    if (inputParser.optionExists(FILENAME_OPTION)) {
        filename = inputParser.getOption(FILENAME_OPTION);
    } else {
        throw IllegalArgumentsException(FILENAME_OPTION_NOT_FOUND);
    }
    if (WORDS_MODE != mode && CHECKSUM_MODE != mode) {
        throw IllegalArgumentsException(INCORRECT_MODE);
    }
    if (WORDS_MODE == mode) {
        if (!inputParser.optionExists(WORD_OPTION)) {
            throw IllegalArgumentsException(OPTION_V_NOT_FOUND);
        }
        word = inputParser.getOption(WORD_OPTION);
        if (word.empty()) {
            throw IllegalArgumentsException(EMPTY_WORD);
        }
    }
    return std::make_tuple(mode, filename, word);
}

uint32_t Utils::getCountWordsInFile(const std::string &filename, const std::string &word) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        throw std::runtime_error("file not found");
    }
    const auto chunkSize = 8; //chunks for testing
    //const auto chunkSize = 1024 * 1024; //normal chunks
    std::vector<char> buffer(chunkSize, 0);

    std::string str;
    std::unordered_map<std::string, uint32_t> countWords;

    while (true) {
        fin.read(buffer.data(), buffer.size());
        std::streamsize s = fin.gcount();
        if (!s) break;
        for (size_t i = 0; i < s; ++i) {
            if (isalpha(buffer[i])) {
                str += buffer[i];
            } else {
                if (!str.empty()) {
                    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
                    countWords[str]++;
                    str.clear();
                }
            }
        }
    }
    std::string lowerCaseWord = word;
    std::transform(lowerCaseWord.begin(), lowerCaseWord.end(), lowerCaseWord.begin(), ::tolower);
    return countWords[lowerCaseWord];
}
