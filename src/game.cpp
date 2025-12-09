#include "game.h"
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

Game::Game() : running(false) {}

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
        universe.nextGeneration();
        
        if (i <= iterations) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
    showStatus();
}

void Game::runOfflineMode(const std::string& inputFile, int iterations, const std::string& outputFile) {
    if (!universe.loadFromFile(inputFile)) {
        std::cerr << "Failed to load universe from: " << inputFile << std::endl;
        return;
    }
    
    std::cout << "Processing " << iterations << " iterations..." << std::endl;
    
    for (int i = 0; i < iterations; ++i) {
        universe.nextGeneration();
    }
    
    if (universe.saveToFile(outputFile)) {
        std::cout << "Result saved to: " << outputFile << std::endl;
    } else {
        std::cerr << "Failed to save result to: " << outputFile << std::endl;
    }
}

void Game::processCommand(const std::string& command) {
    std::stringstream ss(command);
    std::string cmd;
    ss >> cmd;

    if (cmd.empty()) return;
    
    if (cmd == "exit" || cmd == "quit" || cmd == "q") {
        running = false;
    } 
    else if (cmd == "help" || cmd == "h") {
        showHelp();
    }
    else if (cmd == "dump") {
        std::string filename;
        if (ss >> filename) {
            if (universe.saveToFile(filename)) {
                std::cout << "Universe saved to: " << filename << std::endl;
            }
        } else {
            std::cout << "Usage: dump <filename>" << std::endl;
        }
    }
    else if (cmd == "tick" || cmd == "t") {
        int n = 1;
        ss >> n;
        
        if (n <= 0) {
            std::cout << "Error: Number of iterations must be positive!" << std::endl;
            return;
        }
        
        std::cout << "Running " << n << " iteration(s)..." << std::endl;
        for (int i = 0; i < n; ++i) {
            universe.nextGeneration();
        }
        showStatus();
    }
    else if (cmd == "load") {
        std::string filename;
        if (ss >> filename) {
            if (universe.loadFromFile(filename)) {
                std::cout << "Universe loaded from: " << filename << std::endl;
                showStatus();
            }
        } else {
            std::cout << "Usage: load <filename>" << std::endl;
        }
    }
    else if (cmd == "clear") {
        universe.clear();
        std::cout << "Universe cleared" << std::endl;
        showStatus();
    }
    else if (cmd == "status") {
        showStatus();
    }
    else if (cmd == "rule") {
        std::string ruleString;
        if (ss >> ruleString) {
            universe.setRule(Rule(ruleString));
            std::cout << "Rule changed to: " << universe.getRule().toString() << std::endl;
        } else {
            std::cout << "Current rule: " << universe.getRule().toString() 
                      << " (" << universe.getRule().getName() << ")" << std::endl;
        }
    }
    else if (!cmd.empty()) {
        std::cout << "Unknown command: " << cmd << std::endl;
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
    universe.display();
}