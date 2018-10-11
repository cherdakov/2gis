#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma ide diagnostic ignored "cppcoreguidelines-avoid-goto"
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by cherdakov on 09.10.18.
//

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../InputParser.h"
#include "../Utils.h"

using testing::Eq;

namespace {
    class InputParserTest : public testing::Test {
    public:
        InputParserTest() = default;
    };
}

TEST_F(InputParserTest, helpOnlyTest) {
    int argc = 2;
    char **argv = new char *[argc];
    argv[1] = new char[HELP_OPTION.size() + 1];
    strcpy(argv[1], HELP_OPTION.c_str());
    InputParser inputParser(argc, argv);
    ASSERT_EQ(true, inputParser.optionExists(HELP_OPTION));
}

TEST_F(InputParserTest, checkSumModeTest) {
    std::string filename = "ok.txt";
    int argc = 5;
    char **argv = new char *[argc];
    argv[1] = new char[MODE_OPTION.size() + 1];
    argv[2] = new char[CHECKSUM_MODE.size() + 1];
    argv[3] = new char[FILENAME_OPTION.size() + 1];
    argv[4] = new char[filename.size() + 1];
    strcpy(argv[1], MODE_OPTION.c_str());
    strcpy(argv[2], CHECKSUM_MODE.c_str());
    strcpy(argv[3], FILENAME_OPTION.c_str());
    strcpy(argv[4], filename.c_str());
    InputParser inputParser(argc, argv);
    ASSERT_EQ(false, inputParser.optionExists(HELP_OPTION));
    ASSERT_EQ(true, inputParser.optionExists(MODE_OPTION));
    ASSERT_EQ(true, inputParser.optionExists(FILENAME_OPTION));
    ASSERT_EQ(CHECKSUM_MODE, inputParser.getOption(MODE_OPTION));
    ASSERT_EQ(filename, inputParser.getOption(FILENAME_OPTION));

}


TEST_F(InputParserTest, wordsModeTest) {
    int argc = 7;
    char **argv = new char *[argc];
    std::string filename = "ok.txt";
    std::string word = "word";
    argv[1] = new char[MODE_OPTION.size() + 1];
    argv[2] = new char[WORDS_MODE.size() + 1];
    argv[3] = new char[FILENAME_OPTION.size() + 1];
    argv[4] = new char[filename.size() + 1];
    argv[5] = new char[WORD_OPTION.size() + 1];
    argv[6] = new char[word.size() + 1];
    strcpy(argv[1], MODE_OPTION.c_str());
    strcpy(argv[2], WORDS_MODE.c_str());
    strcpy(argv[3], FILENAME_OPTION.c_str());
    strcpy(argv[4], filename.c_str());
    strcpy(argv[5], WORD_OPTION.c_str());
    strcpy(argv[6], word.c_str());
    InputParser inputParser(argc, argv);
    ASSERT_EQ(false, inputParser.optionExists(HELP_OPTION));
    ASSERT_EQ(true, inputParser.optionExists(MODE_OPTION));
    ASSERT_EQ(true, inputParser.optionExists(FILENAME_OPTION));
    ASSERT_EQ(true, inputParser.optionExists(WORD_OPTION));
    ASSERT_EQ(WORDS_MODE, inputParser.getOption(MODE_OPTION));
    ASSERT_EQ(filename, inputParser.getOption(FILENAME_OPTION));
    ASSERT_EQ(word, inputParser.getOption(WORD_OPTION));
}


TEST_F(InputParserTest, wordNotFoundTest) {
    int argc = 6;
    char **argv = new char *[argc];
    std::string file = "ok.txt";
    argv[1] = new char[MODE_OPTION.size() + 1];
    argv[2] = new char[WORDS_MODE.size() + 1];
    argv[3] = new char[FILENAME_OPTION.size() + 1];
    argv[4] = new char[file.size() + 1];
    argv[5] = new char[WORD_OPTION.size() + 1];
    strcpy(argv[1], MODE_OPTION.c_str());
    strcpy(argv[2], WORDS_MODE.c_str());
    strcpy(argv[3], FILENAME_OPTION.c_str());
    strcpy(argv[4], file.c_str());
    strcpy(argv[5], WORD_OPTION.c_str());
    InputParser inputParser(argc, argv);
    ASSERT_THROW(Utils::parseArguments(inputParser), IllegalArgumentsException);
    try {
        Utils::parseArguments(inputParser);
    } catch (IllegalArgumentsException &e) {
        ASSERT_EQ(EMPTY_WORD, e.getMessage());
    }
}


TEST_F(InputParserTest, helpOrModeNotFound) {
    InputParser inputParser(1, nullptr);
    std::string mode, filename, word;
    ASSERT_THROW(Utils::parseArguments(inputParser), IllegalArgumentsException);
    try {
        Utils::parseArguments(inputParser);
    } catch (IllegalArgumentsException &e) {
        ASSERT_EQ(REQUIRED_OPTIONS_NOT_FOUND, e.getMessage());
    }
}

#pragma clang diagnostic pop