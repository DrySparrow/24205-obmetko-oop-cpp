#ifndef WORDSTATISTICS_H
#define WORDSTATISTICS_H

#include <map>
#include <vector>
#include <string>
#include <tuple>

class WordStatistics {
private:
    const std::map<std::string, int>& wordCount;
    std::vector<std::pair<std::string, int>> sortedWords;
    long totalWords;

    void calculateTotal();

public:
    WordStatistics(const std::map<std::string, int>& ws);
    std::vector<std::tuple<std::string, int, double>> getStatistics() const;
};

#endif