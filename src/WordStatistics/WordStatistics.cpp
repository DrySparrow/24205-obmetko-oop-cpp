#include "WordStatistics.h"
#include <algorithm>

WordStatistics::WordStatistics(const std::map<std::string, int>& ws) : wordCount(ws) {
    calculateTotal();
    for (const auto& pair : wordCount) {
        sortedWords.push_back(pair);
    }
    std::sort(sortedWords.begin(), sortedWords.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second;
        });
}

void WordStatistics::calculateTotal() {
    totalWords = 0;
    for (const auto& pair : wordCount) {
        totalWords += pair.second;
    }
}

std::vector<std::tuple<std::string, int, double>> WordStatistics::getStatistics() const {
    std::vector<std::tuple<std::string, int, double>> result;
    for (const auto& item : sortedWords) {
        double percentage = (static_cast<double>(item.second) / totalWords) * 100.0;
        result.emplace_back(item.first, item.second, percentage);
    }
    return result;
}