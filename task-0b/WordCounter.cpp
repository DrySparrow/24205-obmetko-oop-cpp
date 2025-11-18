#include "WordCounter.h"
#include <cctype>

WordCounter::WordCounter(FileReader& reader) : reader(reader) {}

void WordCounter::processLine(const std::string& line) {
    std::string word;
    for (char c : line) {
        if (std::isalnum(c)) {
            word += std::tolower(c);
        } else if (!word.empty()) {
            wordCount[word]++;
            word.clear();
        }
    }
    if (!word.empty()) {
        wordCount[word]++;
    }
}

void WordCounter::countWords() {
    reader.open();
    while (reader.hasNext()) {
        std::string line = reader.next();
        if (!line.empty()) {
            processLine(line);
        }
    }
    reader.close();
}

const std::map<std::string, int>& WordCounter::getWordCount() const {
    return wordCount;
}