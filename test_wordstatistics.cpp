#include <gtest/gtest.h>
#include <map>
#include "WordStatistics.h"

TEST(WordStatisticsTest, SortByFrequency) {
    std::map<std::string, int> wordCount = {
        {"apple", 3},
        {"banana", 1},
        {"cherry", 5},
        {"date", 2}
    };
    
    WordStatistics stats(wordCount);
    auto statistics = stats.getStatistics();
    
    // Should be sorted by frequency descending
    EXPECT_EQ(std::get<0>(statistics[0]), "cherry");
    EXPECT_EQ(std::get<0>(statistics[1]), "apple");
    EXPECT_EQ(std::get<0>(statistics[2]), "date");
    EXPECT_EQ(std::get<0>(statistics[3]), "banana");
}

TEST(WordStatisticsTest, CalculatePercentages) {
    std::map<std::string, int> wordCount = {
        {"word1", 2},
        {"word2", 2}
    };
    
    WordStatistics stats(wordCount);
    auto statistics = stats.getStatistics();
    
    // Each should be 50%
    EXPECT_DOUBLE_EQ(std::get<2>(statistics[0]), 50.0);
    EXPECT_DOUBLE_EQ(std::get<2>(statistics[1]), 50.0);
}

TEST(WordStatisticsTest, SingleWord) {
    std::map<std::string, int> wordCount = {
        {"only", 10}
    };
    
    WordStatistics stats(wordCount);
    auto statistics = stats.getStatistics();
    
    EXPECT_EQ(statistics.size(), 1);
    EXPECT_EQ(std::get<0>(statistics[0]), "only");
    EXPECT_EQ(std::get<1>(statistics[0]), 10);
    EXPECT_DOUBLE_EQ(std::get<2>(statistics[0]), 100.0);
}
