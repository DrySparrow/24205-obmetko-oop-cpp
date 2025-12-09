#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "rule.h"
#include <vector>
#include <string>

class Universe {
private:
    std::string name;
    size_t width;
    size_t height;
    std::vector<std::vector<bool>> grid;
    Rule rule;
    int generation;
    
    int countNeighbors(int x, int y) const;
    
public:
    Universe();
    Universe(size_t w, size_t h, const std::string& n = "Universe");
    Universe(const Universe& other);
    
    void setRule(const Rule& r);
    Rule getRule() const;
    
    void setCell(int x, int y, bool alive);
    bool getCell(int x, int y) const;
    
    void clear();
    void nextGeneration();
    
    bool loadFromFile(const std::string& filename);
    bool saveToFile(const std::string& filename) const;
    
    void display() const;
    
    std::string getName() const;
    void setName(const std::string& newName);
    
    size_t getWidth() const;
    size_t getHeight() const;
    int getGeneration() const;
    
    void resize(size_t w, size_t h);
};

#endif