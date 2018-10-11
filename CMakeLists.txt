cmake_minimum_required(VERSION 3.12)
project(2gis)

set(CMAKE_CXX_STANDARD 17)


add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)
link_libraries(stdc++fs)

add_executable(2gis main.cpp tests/InputParserTest.cpp tests/CountWordsTests.cpp tests/CheckSumTest.cpp InputParser.cpp InputParser.h IllegalArgumentsException.cpp IllegalArgumentsException.h Utils.cpp Utils.h)
target_link_libraries(2gis gtest gtest_main)

