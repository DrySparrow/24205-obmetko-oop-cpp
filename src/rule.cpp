#include "rule.h"
#include <sstream>
#include <algorithm>
#include <iostream>

Rule::Rule() : name("Conway's Game of Life"), birth({3}), survive({2, 3}) {}

Rule::Rule(const std::string& ruleString) {
    *this = parseRuleString(ruleString);
}

Rule::Rule(const std::vector<int>& b, const std::vector<int>& s, const std::string& n) 
    : name(n), birth(b), survive(s) {}

bool Rule::shouldCellLive(bool isAlive, int neighbors) const {
    if (isAlive) {
        return std::find(survive.begin(), survive.end(), neighbors) != survive.end();
    } else {
        return std::find(birth.begin(), birth.end(), neighbors) != birth.end();
    }
}

std::string Rule::toString() const {
    std::stringstream ss;
    ss << "B";
    for (int n : birth) ss << n;
    ss << "/S";
    for (int n : survive) ss << n;
    return ss.str();
}

std::string Rule::getName() const {
    return name;
}

Rule Rule::parseRuleString(const std::string& ruleString) {
    std::vector<int> birth;
    std::vector<int> survive;
    std::string name = "Custom Rule";
    
    if (ruleString.empty()) {
        return getDefaultRule();
    }
    
    size_t slashPos = ruleString.find('/');
    if (slashPos == std::string::npos) {
        std::cerr << "Invalid rule format. Using default rule." << std::endl;
        return getDefaultRule();
    }
    
    std::string birthPart = ruleString.substr(0, slashPos);
    std::string survivePart = ruleString.substr(slashPos + 1);
    
    // Parse birth conditions
    if (birthPart[0] == 'B') {
        for (size_t i = 1; i < birthPart.size(); ++i) {
            if (isdigit(birthPart[i])) {
                birth.push_back(birthPart[i] - '0');
            }
        }
    }
    
    // Parse survive conditions
    if (survivePart[0] == 'S') {
        for (size_t i = 1; i < survivePart.size(); ++i) {
            if (isdigit(survivePart[i])) {
                survive.push_back(survivePart[i] - '0');
            }
        }
    }
    
    return Rule(birth, survive, name);
}

Rule Rule::getDefaultRule() {
    return Rule({3}, {2, 3}, "Conway's Game of Life");
}
