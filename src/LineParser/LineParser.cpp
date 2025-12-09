#include <vector>

#include "LineParser.h"

std::vector<std::string> LineParser::parse(const std::string& line) {
	std::vector<std::string> words;
    std::string word;
    for (char c : line) {
        if (std::isalnum(static_cast<unsigned char>(c))) {
            word += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        } else if (!word.empty()) {
            words.push_back(word);
			word.clear();
        }
    }
    if (!word.empty()) {
        words.push_back(word);
    }
	
	return words;
}
