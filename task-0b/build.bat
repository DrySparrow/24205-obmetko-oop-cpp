@echo off
set GTEST_PATH=C:/Users/Sergey/vcpkg/installed/x64-mingw-dynamic

echo Building main program...
g++ -std=c++17 -I. -o word_count.exe main.cpp FileReader.cpp WordCounter.cpp WordStatistics.cpp CSVWriter.cpp

echo Building tests...
g++ -std=c++17 -I. -I%GTEST_PATH%/include -L%GTEST_PATH%/lib test_filereader.cpp FileReader.cpp test_main.cpp -o test_filereader.exe %GTEST_PATH%/lib/libgtest.dll.a -lpthread
g++ -std=c++17 -I. -I%GTEST_PATH%/include -L%GTEST_PATH%/lib test_wordcounter.cpp FileReader.cpp WordCounter.cpp test_main.cpp -o test_wordcounter.exe %GTEST_PATH%/lib/libgtest.dll.a -lpthread
g++ -std=c++17 -I. -I%GTEST_PATH%/include -L%GTEST_PATH%/lib test_wordstatistics.cpp WordStatistics.cpp test_main.cpp -o test_wordstatistics.exe %GTEST_PATH%/lib/libgtest.dll.a -lpthread
g++ -std=c++17 -I. -I%GTEST_PATH%/include -L%GTEST_PATH%/lib test_csvwriter.cpp CSVWriter.cpp test_main.cpp -o test_csvwriter.exe %GTEST_PATH%/lib/libgtest.dll.a -lpthread

echo Copying DLL...
copy "%GTEST_PATH%/bin/libgtest.dll" .

echo Done!