cmake_minimum_required(VERSION 3.14)
project(WordCount)

set(CMAKE_CXX_STANDARD 23)

set(GTEST_PATH "C:/Users/Sergey/vcpkg/installed/x64-mingw-static")
set(GTEST_INCLUDE_DIR "${GTEST_PATH}/include")
include_directories(${GTEST_INCLUDE_DIR})

# Основная программа
add_executable(word_count 
    main.cpp
    FileReader.cpp 
    WordCounter.cpp 
    WordStatistics.cpp 
    CSVWriter.cpp
)

add_executable(run_all_tests 
    test_main.cpp
    test_filereader.cpp 
    test_wordcounter.cpp 
    test_wordstatistics.cpp 
    test_csvwriter.cpp
    FileReader.cpp 
    WordCounter.cpp 
    WordStatistics.cpp 
    CSVWriter.cpp
)

target_link_libraries(run_all_tests ${GTEST_PATH}/lib/libgtest.a)
