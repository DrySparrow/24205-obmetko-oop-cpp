#include "WordCounter.h"
#include <cctype>

void WordCounter::handle(const std::string& word) {
    wordCount[word]++;
}

void WordCounter::handle(const std::vector<std::string>& line) {
    for (const auto& word : line) {
        handle(word);
    }
}

const std::map<std::string, int>& WordCounter::getWordCount() const {
    return wordCount;
}
