#include "universe.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

const int WIDTH = 20;
const int HEIGHT = 20;

Universe::Universe() : name("Universe"), width(WIDTH), height(HEIGHT), grid(HEIGHT, std::vector<bool>(WIDTH, false)), 
                      rule(Rule::getDefaultRule()), generation(0) {}

Universe::Universe(size_t w, size_t h, const std::string& n) 
    : name(n), width(w), height(h), grid(h, std::vector<bool>(w, false)), 
      rule(Rule::getDefaultRule()), generation(0) {}

Universe::Universe(const Universe& other)
    : name(other.name), width(other.width), height(other.height), 
      grid(other.grid), rule(other.rule), generation(other.generation) {}

void Universe::setRule(const Rule& r) {
    rule = r;
}

Rule Universe::getRule() const {
    return rule;
}

void Universe::setCell(int x, int y, bool alive) {
    if (x >= 0 && x < static_cast<int>(width) && y >= 0 && y < static_cast<int>(height)) {
        grid[y][x] = alive;
    }
}

bool Universe::getCell(int x, int y) const {
    if (x >= 0 && x < static_cast<int>(width) && y >= 0 && y < static_cast<int>(height)) {
        return grid[y][x];
    }
    return false;
}

void Universe::clear() {
    for (auto& row : grid) {
        std::fill(row.begin(), row.end(), false);
    }
    generation = 0;
}

int Universe::countNeighbors(int x, int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            
            // Toroidal wrapping
            int nx = (x + dx + static_cast<int>(width)) % static_cast<int>(width);
            int ny = (y + dy + static_cast<int>(height)) % static_cast<int>(height);
            
            if (grid[ny][nx]) {
                count++;
            }
        }
    }
    return count;
}

void Universe::nextGeneration() {
    std::vector<std::vector<bool>> newGrid = grid;
    
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            int neighbors = countNeighbors(static_cast<int>(x), static_cast<int>(y));
            bool isAlive = grid[y][x];
            
            newGrid[y][x] = rule.shouldCellLive(isAlive, neighbors);
        }
    }
    
    grid = newGrid;
    generation++;
}

bool Universe::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return false;
    }
    
    std::string line;
    if (!std::getline(file, line)) {
        std::cerr << "File is empty: " << filename << std::endl;
        return false;
    }
    
    // Check if it's Life 1.06 format
    if (line == "#Life 1.06") {
        clear();
        
        int centerX = static_cast<int>(width) / 2;
        int centerY = static_cast<int>(height) / 2;
        
        int x, y;
        int cellsLoaded = 0;
        while (file >> x >> y) {
            int col = x + centerX;
            int row = y + centerY;
            
            if (col >= 0 && col < static_cast<int>(width) && 
                row >= 0 && row < static_cast<int>(height)) {
                grid[row][col] = true;
                cellsLoaded++;
            }
        }
        
        file.close();
        generation = 0;
        name = filename;
        
        std::cout << "Loaded " << cellsLoaded << " cells from " << filename << std::endl;
        return cellsLoaded > 0;
    }
    
    file.close();
    std::cerr << "Unsupported file format: " << filename << std::endl;
    return false;
}

bool Universe::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file for writing: " << filename << std::endl;
        return false;
    }
    
    file << "#Life 1.06\n";
    
    int centerX = static_cast<int>(width) / 2;
    int centerY = static_cast<int>(height) / 2;
    
    int cellsSaved = 0;
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            if (grid[y][x]) {
                int fileX = static_cast<int>(x) - centerX;
                int fileY = static_cast<int>(y) - centerY;
                file << fileX << " " << fileY << "\n";
                cellsSaved++;
            }
        }
    }
    
    file.close();
    std::cout << "Saved " << cellsSaved << " cells to " << filename << std::endl;
    return true;
}

void Universe::display() const {
    std::cout << "\nUniverse: " << name << std::endl;
    std::cout << "Rule: " << rule.toString() << " (" << rule.getName() << ")" << std::endl;
    std::cout << "Generation: " << generation << std::endl;
    std::cout << "Size: " << width << "x" << height << std::endl;
    
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            std::cout << (grid[y][x] ? "|#|" : "| |");
        }
        std::cout << std::endl;
    }
}

std::string Universe::getName() const {
    return name;
}

void Universe::setName(const std::string& newName) {
    name = newName;
}

size_t Universe::getWidth() const {
    return width;
}

size_t Universe::getHeight() const {
    return height;
}

int Universe::getGeneration() const {
    return generation;
}

void Universe::resize(size_t w, size_t h) {
    width = w;
    height = h;
    grid = std::vector<std::vector<bool>>(h, std::vector<bool>(w, false));
}