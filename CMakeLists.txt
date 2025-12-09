cmake_minimum_required(VERSION 3.14)
project(WordCount)

set(CMAKE_CXX_STANDARD 23)

# Настройки для Google Test (vcpkg)
set(GTEST_PATH "C:/Users/Sergey/vcpkg/installed/x64-mingw-static")
set(GTEST_INCLUDE_DIR "${GTEST_PATH}/include")
set(GTEST_LIBRARY "${GTEST_PATH}/lib/libgtest.a")
set(GTEST_MAIN_LIBRARY "${GTEST_PATH}/lib/libgtest_main.a")

# Включить тестирование
enable_testing()

# Основная программа
add_executable(word_count 
    src/main.cpp
    src/FileReader/FileReader.cpp 
    src/WordCounter/WordCounter.cpp 
    src/WordStatistics/WordStatistics.cpp 
    src/CSVWriter/CSVWriter.cpp
)

# Заголовочные файлы для основного приложения
target_include_directories(word_count 
    PRIVATE
    src/FileReader
    src/WordCounter
    src/WordStatistics
    src/CSVWriter
)

# Исполняемый файл для тестов
add_executable(run_all_tests
    tests/test_main.cpp
    tests/test_filereader.cpp
    tests/test_wordcounter.cpp
    tests/test_wordstatistics.cpp
    tests/test_csvwriter.cpp
    src/FileReader/FileReader.cpp
    src/WordCounter/WordCounter.cpp
    src/WordStatistics/WordStatistics.cpp
    src/CSVWriter/CSVWriter.cpp
)

# Заголовочные файлы для тестов
target_include_directories(run_all_tests 
    PRIVATE
    ${GTEST_INCLUDE_DIR}
    src/FileReader
    src/WordCounter
    src/WordStatistics
    src/CSVWriter
    tests
)

# Связывание с библиотеками Google Test
target_link_libraries(run_all_tests 
    ${GTEST_LIBRARY}
    ${GTEST_MAIN_LIBRARY}
)

# Добавить тест в CTest
add_test(NAME AllTests COMMAND run_all_tests)

# Копирование тестовых данных в build для тестов
configure_file(${CMAKE_SOURCE_DIR}/data/in.txt ${CMAKE_BINARY_DIR}/data/in.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/data/test_output.csv ${CMAKE_BINARY_DIR}/data/test_output.csv COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/data/test_precision.csv ${CMAKE_BINARY_DIR}/data/test_precision.csv COPYONLY)