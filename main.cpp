#include <string>
#include <iostream>
#include <vector>
#include <cctype>
#include <fstream>
#include <unordered_map>
#include <algorithm>

static const std::string HELP_MODE = "help";
static const std::string CHECKSUM_MODE = "checksum";
static const std::string COUNT_WORDS_MODE = "words";
static const std::string HELP_MESSAGE = "2gis one love?";

class InputParser {
public:
    InputParser(int argc, char **argv) {
        for (int i = 1; i < argc; ++i) {
            this->tokens.emplace_back(argv[i]);
        }
    }

    const std::string& getOption(const std::string& option) const {
        auto it = std::find(this->tokens.begin(), this->tokens.end(), option);
        if (it != this->tokens.end() && ++it != this->tokens.end()) {
            return *it;
        }
        static const std::string empty_string;
        return empty_string;
    }

    bool optionExists(const std::string &option) const {
        return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
    }

private:
    std::vector<std::string> tokens;
};

uint32_t getCountWordsInFile(const std::string& filename, const std::string& word) {
    std::ifstream fin(filename);
    if(!fin.is_open()){

    }
    const auto chunkSize = 16 * 1024;
    std::vector<char> buffer(chunkSize, 0);

    std::string str;
    std::unordered_map<std::string, uint32_t> countWords;

    while (fin.read(buffer.data(), buffer.size())) {
        std::streamsize s = fin.gcount();
        for (size_t i = 0; i < s; ++i) {
            if (isalpha(buffer[i])) {
                str += buffer[i];
            } else {
                if (!str.empty()) {
                    countWords[str]++;
                    str.clear();
                }
            }
        }
    }
    return countWords[word];
}

uint32_t getFileCheckSum(const std::string &filename) {
    return 0;
}

class IllegalArgumentsException : public std::exception {
private:
    std::string message;
public:
    explicit IllegalArgumentsException(std::string message) : message(std::move(message)) {}

    const std::string& getMessage() {
        return message;
    }

    const char* what() {
        return "IllegalArgumentsException";
    }
};

void parseArguments(const InputParser& inputParser, std::string& mode, std::string& filename, std::string& word) {
    if (inputParser.optionExists("-h")) {
        mode = "help";
        return;
    }
    if (inputParser.optionExists("-m")) {
        mode = inputParser.getOption("-m");
    } else {
        throw IllegalArgumentsException("Mode option does not exists");
    }
    if (inputParser.optionExists("-f")) {
        filename = inputParser.getOption("-f");
    } else {
        throw IllegalArgumentsException("Filename option does not exists");
    }
    if ("words" != mode && "checksum" != mode) {
        throw IllegalArgumentsException("Incorrect mode");
    }
    if ("words" == mode) {
        if (!inputParser.optionExists("-v")) {
            throw IllegalArgumentsException("-v required for this mode");
        }
        word = inputParser.getOption("-v");
        if (word.empty()) {
            throw IllegalArgumentsException("word is empty");
        }
    }
}

int main(int argc, char **argv) {
    InputParser inputParser(argc, argv);
    std::string mode, filename, word;
    try {
        parseArguments(inputParser, mode, filename, word);
        if (HELP_MODE == mode) {
            std::cout << HELP_MESSAGE << std::endl;
        } else if (CHECKSUM_MODE == mode) {
            auto checkSum = getFileCheckSum(filename);
            std::cout << "checkSum:" << checkSum << std::endl;
        } else if (COUNT_WORDS_MODE == mode) {
            auto count = getCountWordsInFile(filename, word);
            std::cout << "count:" << count << std::endl;
        }
    } catch (IllegalArgumentsException& e) {
        std::cout << e.getMessage() << std::endl;
    } catch (std::ifstream::failure& e){
        std::cout << e.what() << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}