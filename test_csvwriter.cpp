#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "CSVWriter.h"

TEST(CSVWriterTest, WriteData) {
    CSVWriter writer("test_output.csv");
    std::vector<std::tuple<std::string, int, double>> data = {
        {"apple", 5, 50.0},
        {"banana", 3, 30.0},
        {"cherry", 2, 20.0}
    };
    
    writer.open();
    writer.write(data);
    writer.close();
    
    // Verify file content
    std::ifstream outputFile("test_output.csv");
    std::stringstream buffer;
    buffer << outputFile.rdbuf();
    std::string content = buffer.str();
    
    EXPECT_TRUE(content.find("apple,5,50.00") != std::string::npos);
    EXPECT_TRUE(content.find("banana,3,30.00") != std::string::npos);
    EXPECT_TRUE(content.find("cherry,2,20.00") != std::string::npos);
    
    remove("test_output.csv");
}

TEST(CSVWriterTest, FileCreation) {
    CSVWriter writer("test_create.csv");
    
    EXPECT_NO_THROW(writer.open());
    writer.close();
    
    // Check if file was created
    std::ifstream testFile("test_create.csv");
    EXPECT_TRUE(testFile.good());
    testFile.close();
    
    remove("test_create.csv");
}

TEST(CSVWriterTest, PrecisionFormatting) {
    CSVWriter writer("test_precision.csv");
    std::vector<std::tuple<std::string, int, double>> data = {
        {"test", 1, 33.333333}
    };
    
    writer.open();
    writer.write(data);
    writer.close();
    
    std::ifstream outputFile("test_precision.csv");
    std::string line;
    std::getline(outputFile, line);
    
    EXPECT_EQ(line, "test,1,33.33");
    
    remove("test_precision.csv");
}
