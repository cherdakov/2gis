//
// Created by cherdakov on 09.10.18.
//

#include <gtest/gtest.h>
#include "../Utils.h"
#include <experimental/filesystem>
#include <gmock/gmock-matchers.h>

using testing::Eq;
namespace fs = std::experimental::filesystem;

namespace {
    class CountWordsTest : public testing::Test {
    public:
        CountWordsTest() {

        }
    };
}


TEST_F(CountWordsTest, fileNotExistsTest) {
    std::string filename = "fileNotExists.txt";
    ASSERT_THROW(Utils::getFileCheckSum(filename), std::exception);
}

TEST_F(CountWordsTest, fewShortTests) {
    std::string filename = "fewShortTests.txt";
    std::ofstream fout(filename);
    std::string text = "Some&feAtures may!not be.available iftheyare "
                       "nOt'supported by thE underlying file SySteM!";
    fout << text;
    fout.close();
    ASSERT_EQ(Utils::getCountWordsInFile(filename, "mother"), 0);
    ASSERT_EQ(Utils::getCountWordsInFile(filename, "lable"), 0);
    ASSERT_EQ(Utils::getCountWordsInFile(filename, "are"), 0);
    ASSERT_EQ(Utils::getCountWordsInFile(filename, "they"), 0);
    ASSERT_EQ(Utils::getCountWordsInFile(filename, "Available"), 1);
    ASSERT_EQ(Utils::getCountWordsInFile(filename, "not"), 2);
    ASSERT_EQ(Utils::getCountWordsInFile(filename, "system"), 1);
    ASSERT_EQ(Utils::getCountWordsInFile(filename, "fILe"), 1);
    ASSERT_EQ(Utils::getCountWordsInFile(filename, "by"), 1);
    ASSERT_EQ(Utils::getCountWordsInFile(filename, "suPPorted"), 1);
    ASSERT_EQ(Utils::getCountWordsInFile(filename, "Some"), 1);
    fs::remove(filename);
}