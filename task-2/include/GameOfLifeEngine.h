#ifndef GAMEOFLIFEENGINE_H
#define GAMEOFLIFEENGINE_H

#include "Universe.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class GameOfLifeEngine {
private:
    Universe* universe;
    
    std::array<std::vector<int>, 2> parseRuleString(const std::string& ruleString);

public:
    GameOfLifeEngine();
    GameOfLifeEngine(size_t w, size_t h, const std::string& n = "Universe");
    GameOfLifeEngine(const GameOfLifeEngine& other);
    ~GameOfLifeEngine();

    GameOfLifeEngine& operator=(const GameOfLifeEngine& other);
    
    void setRule(const std::string newRule);
    
    static std::array<std::vector<int>, 2> getDefaultRule();
    std::array<std::vector<int>, 2> getRule() const;

    std::string getStringRule() const;
    
    void setCell(int x, int y, bool alive);
    bool getCell(int x, int y) const;
    
    void clear();
    void nextGeneration();

    int countNeighbors(int x, int y) const;
    bool shouldCellLive(bool isAlive, int neighbors) const;
    
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