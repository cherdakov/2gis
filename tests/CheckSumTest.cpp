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
    class CheckSumTest : public testing::Test {
    public:
        CheckSumTest() {

        }
    };
}

TEST_F(CheckSumTest, fileNotExistsTest) {
    std::string filename = "fileNotExists.txt";
    ASSERT_THROW(Utils::getFileCheckSum(filename), std::exception);
}

TEST_F(CheckSumTest, copyFileTest) {
    std::string originalFileName = "sample.txt";
    std::string copyFileName = "copy." + originalFileName;
    if (fs::exists(originalFileName)) {
        fs::remove(originalFileName);
    }
    if (fs::exists(copyFileName)) {
        fs::remove(copyFileName);
    }
    std::ofstream fout(originalFileName);
    fout << "same data";
    fout.close();
    fs::copy_file(originalFileName, copyFileName);
    ASSERT_EQ(Utils::getFileCheckSum(originalFileName), Utils::getFileCheckSum(copyFileName));
    fs::remove(originalFileName);
    fs::remove(copyFileName);
}

TEST_F(CheckSumTest, precalculateCheckSumTest) {
    std::vector<uint32_t> words;
    uint32_t checksum = 0;
    for (size_t i = 0; i < 1024 * 1024; ++i) {
        auto currentWord = static_cast<uint32_t>(rand());
        words.push_back(currentWord);
        checksum += currentWord;
    }
    std::string filename = "precalculateCheckSumTestFile.txt";
    std::ofstream file(filename);
    file.write(reinterpret_cast<char *>(words.data()), words.size() * 4);
    ASSERT_EQ(Utils::getFileCheckSum(filename), checksum);
    fs::remove(filename);
}

TEST_F(CheckSumTest, emptyFileCheckSumTest) {
    std::string filename = "emptyFile.txt";
    std::ofstream fout(filename);
    fout.close();
    ASSERT_NO_THROW(Utils::getFileCheckSum(filename));
    ASSERT_EQ(0, Utils::getFileCheckSum(filename));
    fs::remove(filename);
}
