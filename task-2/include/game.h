#ifndef GAME_H
#define GAME_H

#include "universe.h"
#include <string>

class Game {
private:
    Universe universe;
    bool running;
    
public:
    Game();
    
    void runInteractive();
    void runTickMode(int iterations);
    int runOfflineMode(const std::string& inputFile, int iterations, const std::string& outputFile);
    
private:
    void processCommand(const std::string& command);
    void showHelp() const;
    void showStatus() const;
};

#endif