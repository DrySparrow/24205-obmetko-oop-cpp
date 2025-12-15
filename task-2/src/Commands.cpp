// Commands.hpp
#ifndef COMMANDS_H
#define COMMANDS_H

#include "Command.cpp"
#include "game.h"
#include "GameOfLifeEngine.h"
#include <iostream>

class TickCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override {
        int n = 1;
        args >> n;
        
        if (n <= 0) {
            std::cout << "Error: Number of iterations must be positive!" << std::endl;
            return;
        }
        
        for (int i = 0; i < n; ++i) {
            game.engine.nextGeneration();
        }
        game.showStatus();
    }
    
    std::string getName() const override { return "tick"; }
};

class HelpCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override {
        game.showHelp();
    }
    
    std::string getName() const override { return "help"; }
};

class DumpCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override {
        std::string filename;
        if (args >> filename) {
            if (game.engine.saveToFile(filename)) {
                std::cout << "Universe saved to: " << filename << std::endl;
            } else {
                std::cout << "Error: Failed to save universe!" << std::endl;
            }
        } else {
            std::cout << "Usage: dump <filename>" << std::endl;
        }
    }
    
    std::string getName() const override { return "dump"; }
};

class ExitCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override {
        game.running = false;
    }
    
    std::string getName() const override { return "exit"; }
};

class LoadCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override {
        std::string filename;
        if (args >> filename) {
            if (game.engine.loadFromFile(filename)) {
                std::cout << "Universe loaded from: " << filename << std::endl;
                game.showStatus();
            } else {
                std::cout << "Error: Failed to load universe!" << std::endl;
            }
        } else {
            std::cout << "Usage: load <filename>" << std::endl;
        }
    }
    
    std::string getName() const override { return "load"; }
};

class ClearCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override {
        game.engine.clear();
        std::cout << "Universe cleared" << std::endl;
        game.showStatus();
    }
    
    std::string getName() const override { return "clear"; }
};

class StatusCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override {
        game.showStatus();
    }
    
    std::string getName() const override { return "status"; }
};

class RuleCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override {
        std::string ruleString;
        if (args >> ruleString) {
            game.engine.setRule(ruleString);
            std::cout << "Rule changed to: " << game.engine.getStringRule() << std::endl;
        } else {
            std::cout << "Current rule: " << game.engine.getStringRule() << std::endl;
        }
    }
    
    std::string getName() const override { return "rule"; }
};

#endif