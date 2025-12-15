#include "../include/GameOfLifeEngine.h"
#include "../include/Universe.h"



GameOfLifeEngine::GameOfLifeEngine() : universe(new Universe()) {}

GameOfLifeEngine::GameOfLifeEngine(size_t w, size_t h, const std::string& n) 
    : universe(new Universe(w, h, n)) {}

GameOfLifeEngine::GameOfLifeEngine(const GameOfLifeEngine& other) 
    : universe(new Universe(*other.universe)) {}

std::array<std::vector<int>, 2> GameOfLifeEngine::getDefaultRule() {
    return {std::vector{3}, std::vector{2, 3}};
}

GameOfLifeEngine::~GameOfLifeEngine() {
    delete universe;
}

GameOfLifeEngine& GameOfLifeEngine::operator=(const GameOfLifeEngine& other) {
    if (this != &other) {
        delete universe;
        universe = new Universe(*other.universe);
    }
    return *this;
}

std::array<std::vector<int>, 2> GameOfLifeEngine::parseRuleString(const std::string& ruleString) {
    std::vector<int> birth;
    std::vector<int> survive;
    
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
    
    return {birth, survive};
}

void GameOfLifeEngine::setRule(const std::string newRule) {
    universe->rule = parseRuleString(newRule);
}

std::array<std::vector<int>, 2> GameOfLifeEngine::getRule() const {
    return universe->rule;
}

std::string GameOfLifeEngine::getStringRule() const {
    std::stringstream ss;
    ss << "B";
    for (int n : universe->rule[0]) ss << n;
    ss << "/S";
    for (int n : universe->rule[1]) ss << n;
    return ss.str();
}

void GameOfLifeEngine::setCell(int x, int y, bool alive) {
    if (x >= 0 && x < static_cast<int>(universe->width) && y >= 0 && y < static_cast<int>(universe->height)) {
        universe->grid[y][x] = alive;
    }
}

bool GameOfLifeEngine::getCell(int x, int y) const {
    if (x >= 0 && x < static_cast<int>(universe->width) && y >= 0 && y < static_cast<int>(universe->height)) {
        return universe->grid[y][x];
    }
    return false;
}

void GameOfLifeEngine::clear() {
    for (auto& row : universe->grid) {
        std::fill(row.begin(), row.end(), false);
    }
    universe->generation = 0;
}

void GameOfLifeEngine::nextGeneration() {
    std::vector<std::vector<bool>> newGrid = universe->grid;
    
    for (size_t y = 0; y < universe->height; y++) {
        for (size_t x = 0; x < universe->width; x++) {
            int neighbors = countNeighbors(static_cast<int>(x), static_cast<int>(y));
            bool isAlive = universe->grid[y][x];
            
            newGrid[y][x] = shouldCellLive(isAlive, neighbors);
        }
    }
    
    universe->grid = newGrid;
    (universe->generation)++;
}

int GameOfLifeEngine::countNeighbors(int x, int y) const {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dx == 0 && dy == 0) continue;
            
            // Toroidal wrapping
            int nx = (x + dx + static_cast<int>(universe->width)) % static_cast<int>(universe->width);
            int ny = (y + dy + static_cast<int>(universe->height)) % static_cast<int>(universe->height);
            
            if (universe->grid[ny][nx]) {
                count++;
            }
        }
    }
    return count;
}

bool GameOfLifeEngine::shouldCellLive(bool isAlive, int neighbors) const {
    if (isAlive) {
        return std::find(universe->rule[1].begin(), universe->rule[1].end(), neighbors) != universe->rule[1].end();
    } else {
        return std::find(universe->rule[0].begin(), universe->rule[0].end(), neighbors) != universe->rule[0].end();
    }
}

bool GameOfLifeEngine::loadFromFile(const std::string& filename) {
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
        
        int centerX = static_cast<int>(universe->width) / 2;
        int centerY = static_cast<int>(universe->height) / 2;
        
        int x, y;
        int cellsLoaded = 0;
        while (file >> x >> y) {
            int col = x + centerX;
            int row = y + centerY;
            
            if (col >= 0 && col < static_cast<int>(universe->width) && 
                row >= 0 && row < static_cast<int>(universe->height)) {
                universe->grid[row][col] = true;
                cellsLoaded++;
            }
        }
        
        file.close();
        universe->generation = 0;
        universe->name = filename;
        
        std::cout << "Loaded " << cellsLoaded << " cells from " << filename << std::endl;
        return cellsLoaded > 0;
    }
    
    file.close();
    std::cerr << "Unsupported file format: " << filename << std::endl;
    return false;
}

bool GameOfLifeEngine::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file for writing: " << filename << std::endl;
        return false;
    }
    
    file << "#Life 1.06\n";
    
    int centerX = static_cast<int>(universe->width) / 2;
    int centerY = static_cast<int>(universe->height) / 2;
    
    int cellsSaved = 0;
    for (size_t y = 0; y <universe->height; y++) {
        for (size_t x = 0; x < universe->width; x++) {
            if (universe->grid[y][x]) {
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

void GameOfLifeEngine::display() const {
    std::cout << "\nUniverse: " << universe->name << std::endl;
    std::cout << "Rule: " << getStringRule() << std::endl;
    std::cout << "Generation: " << universe->generation << std::endl;
    std::cout << "Size: " << universe->width << "x" << universe->height << std::endl;
    
    for (size_t y = 0; y < universe->height; y++) {
        for (size_t x = 0; x < universe->width; x++) {
            std::cout << (universe->grid[y][x] ? "|#|" : "| |");
        }
        std::cout << std::endl;
    }
}

std::string GameOfLifeEngine::getName() const {
    return universe->name;
}

void GameOfLifeEngine::setName(const std::string& newName) {
    universe->name = newName;
}

size_t GameOfLifeEngine::getWidth() const {
    return universe->width;
}

size_t GameOfLifeEngine::getHeight() const {
    return universe->height;
}

int GameOfLifeEngine::getGeneration() const {
    return universe->generation;
}

void GameOfLifeEngine::resize(size_t w, size_t h) {
    universe->width = w;
    universe->height = h;
    universe->grid = std::vector<std::vector<bool>>(h, std::vector<bool>(w, false));
}