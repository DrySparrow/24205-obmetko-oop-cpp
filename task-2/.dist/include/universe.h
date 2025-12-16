#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <array>
#include <vector>
#include <string>

class Universe {
public:
    std::string name;
    size_t width = 30;
    size_t height = 20;
    std::vector<std::vector<bool>> grid;
    std::array<std::vector<int>, 2> rule{{ {3}, {2, 3} }};
    int generation = 0; // Инициализируйте здесь
    
    Universe();
    Universe(size_t w, size_t h, const std::string& n = "Universe");
    Universe(const Universe& other);
};

#endif