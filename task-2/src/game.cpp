#include "../include/game.h"
#include "../include/CommandQualifier.h"
#include "../include/Command.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

Game::Game() : running(false), commandQualifier(std::make_unique<CommandQualifier>()) {}

void Game::runInteractive() {
    running = true;
    std::string command;
    
    std::cout << "=== Game of Life ===" << std::endl;
    std::cout << "Type 'help' for available commands" << std::endl;
    showStatus();
    
    while (running) {
        std::cout << "\n> ";
        std::getline(std::cin, command);
        processCommand(command);
    }
}

void Game::runTickMode(int iterations) {
    if (iterations <= 0) {
        std::cerr << "Error: Number of iterations must be positive!" << std::endl;
        return;
    }
    
    for (int i = 0; i < iterations; ++i) {
        showStatus();
        engine.nextGeneration();
        
        if (i <= iterations) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    showStatus();
}

int Game::runOfflineMode(const std::string& inputFile, int iterations, const std::string& outputFile) {
    if (!engine.loadFromFile(inputFile)) {
        std::cerr << "Failed to load universe from: " << inputFile << std::endl;
        return 1;
    }
    
    std::cout << "Processing " << iterations << " iterations..." << std::endl;
    
    for (int i = 0; i < iterations; ++i) {
        engine.nextGeneration();
    }
    
    if (engine.saveToFile(outputFile)) {
        std::cout << "Result saved to: " << outputFile << std::endl;
    } else {
        std::cerr << "Failed to save result to: " << outputFile << std::endl;
    }
    return 0;
}

void Game::processCommand(const std::string& command) {
    if (command.empty()) return;
    
    std::stringstream ss(command);
    std::string cmdName;
    ss >> cmdName;
    
    std::shared_ptr<Command> cmd = commandQualifier->qualifyCommand(cmdName);
    
    if (cmd) {
        cmd->execute(*this, ss);
    } else {
        std::cout << "Unknown command: " << cmdName << std::endl;
        std::cout << "Type 'help' for available commands" << std::endl;
    }
}

void Game::showHelp() const {
    std::cout << std::endl;
    std::cout << "Available commands:" << std::endl;
    std::cout << "  help, h                - Show this help message" << std::endl;
    std::cout << "  dump <filename>        - Save universe to file" << std::endl;
    std::cout << "  tick [n], t [n]        - Calculate n iterations (default: 1)" << std::endl;
    std::cout << "  load <filename>        - Load universe from file" << std::endl;
    std::cout << "  clear                  - Clear the universe" << std::endl;
    std::cout << "  rule [Bx/Sy]           - Show or change rule (e.g., B3/S23)" << std::endl;
    std::cout << "  status                 - Show current status" << std::endl;
    std::cout << "  exit, quit, q          - Exit the game" << std::endl;
}

void Game::showStatus() const {
    engine.display();
}