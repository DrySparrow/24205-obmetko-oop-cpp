#ifndef RULE_H
#define RULE_H

#include <string>
#include <vector>

class Rule {
private:
    std::string name;
    std::vector<int> birth;
    std::vector<int> survive;
    
public:
    Rule();
    Rule(const std::string& ruleString);
    Rule(const std::vector<int>& b, const std::vector<int>& s, const std::string& n = "Custom");
    
    bool shouldCellLive(bool isAlive, int neighbors) const;
    std::string toString() const;
    std::string getName() const;
    
    static Rule parseRuleString(const std::string& ruleString);
    static Rule getDefaultRule();
};

#endif