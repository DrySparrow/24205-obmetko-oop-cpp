#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include "FileReader.h"
#include <map>
#include <string>

class WordCounter {
private:
    FileReader& reader;
    std::map<std::string, int> wordCount;
    
    void processLine(const std::string& line);

public:
    WordCounter(FileReader& reader);
    void countWords();
    const std::map<std::string, int>& getWordCount() const;
};

#endif