#include <gtest/gtest.h>
#include <fstream>
#include "FileReader.h"
#include "WordCounter.h"

class WordCounterTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Create test file with various words and separators
        std::ofstream testFile("test_count.txt");
        testFile << "Hello, world! This is a test.\n";
        testFile << "Another line: with different; separators.";
        testFile.close();
    }

    void TearDown() override {
        remove("test_count.txt");
    }
};

TEST_F(WordCounterTest, CountWordsBasic) {
    FileReader reader("test_count.txt");
    WordCounter counter;
    reader.open();
    while (reader.hasNext()) {
        counter.handle(reader.next());
    }
    reader.close();
    
    auto wordCount = counter.getWordCount();
    
    EXPECT_EQ(wordCount["hello"], 1);
    EXPECT_EQ(wordCount["world"], 1);
    EXPECT_EQ(wordCount["this"], 1);
    EXPECT_EQ(wordCount["is"], 1);
    EXPECT_EQ(wordCount["a"], 1);
    EXPECT_EQ(wordCount["test"], 1);
    EXPECT_EQ(wordCount["another"], 1);
    EXPECT_EQ(wordCount["line"], 1);
    EXPECT_EQ(wordCount["with"], 1);
    EXPECT_EQ(wordCount["different"], 1);
    EXPECT_EQ(wordCount["separators"], 1);
}

TEST_F(WordCounterTest, CaseInsensitive) {
    std::ofstream testFile("test_case.txt");
    testFile << "Hello HELLO hello";
    testFile.close();
    
    FileReader reader("test_case.txt");
    WordCounter counter;
    reader.open();
    while (reader.hasNext()) {
        counter.handle(reader.next());
    }
    reader.close();
    
    auto wordCount = counter.getWordCount();
    EXPECT_EQ(wordCount["hello"], 3);
    
    remove("test_case.txt");
}

TEST_F(WordCounterTest, SeparatorsHandling) {
    std::ofstream testFile("test_separators.txt");
    testFile << "word1,word2;word3:word4.word5!word6?word7";
    testFile.close();
    
    FileReader reader("test_separators.txt");
    WordCounter counter;
    reader.open();
    while (reader.hasNext()) {
        counter.handle(reader.next());
    }
    reader.close();
    
    auto wordCount = counter.getWordCount();
    EXPECT_EQ(wordCount["word1"], 1);
    EXPECT_EQ(wordCount["word2"], 1);
    EXPECT_EQ(wordCount["word3"], 1);
    EXPECT_EQ(wordCount["word4"], 1);
    EXPECT_EQ(wordCount["word5"], 1);
    EXPECT_EQ(wordCount["word6"], 1);
    EXPECT_EQ(wordCount["word7"], 1);
    
    remove("test_separators.txt");
}
