#include "WordCounter.h"
#include <cctype>

void WordCounter::handle(const std::string& line) {
    std::string word;
    for (char c : line) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            word += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        } else if (!word.empty()) {
            wordCount[word]++;
            word.clear();
        }
    }
    if (!word.empty()) {
        wordCount[word]++;
    }
}

void WordCounter::handle(const std::vector<std::string>& lines) {
    for (const auto& line : lines) {
        handle(line);  // используем существующий метод
    }
}

const std::map<std::string, int>& WordCounter::getWordCount() const {
    return wordCount;
}