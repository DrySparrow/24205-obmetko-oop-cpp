#ifndef GAME_H
#define GAME_H

#include "GameOfLifeEngine.h"
#include "CommandQualifier.h"
#include <memory>
#include <string>

class Game {    
public:
    bool running;
    GameOfLifeEngine engine;
    std::unique_ptr<CommandQualifier> commandQualifier;
    Game();
    
    void runInteractive();
    void runTickMode(int iterations);
    int runOfflineMode(const std::string& inputFile, int iterations, const std::string& outputFile);
    
    void processCommand(const std::string& command);
    void showHelp() const;
    void showStatus() const;
};

#endif