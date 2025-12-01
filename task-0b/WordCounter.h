#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include "FileReader.h"
#include <map>
#include <string>
#include <vector>

class WordCounter {
private:
    std::map<std::string, int> wordCount;

public:
    void handle(const std::string& line);
    void handle(const std::vector<std::string>& lines);
    const std::map<std::string, int>& getWordCount() const;
};

#endif