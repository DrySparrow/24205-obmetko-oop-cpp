#ifndef LINEPARSER_H
#define LINEPARSER_H

#include <iostream>

class LineParser {
public:
	std::vector<std::string> parse(const std::string& line);
};

#endif
