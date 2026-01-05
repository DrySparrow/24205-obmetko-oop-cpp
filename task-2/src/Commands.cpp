#include "commands.h"
#include "game.h"
#include "GameOfLifeEngine.h"
#include <iostream>

void TickCommand::execute(Game& game, std::istream& args) const {
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

std::string TickCommand::getName() const {
    return "tick";
}

void HelpCommand::execute(Game& game, std::istream& args) const {
    game.showHelp();
}

std::string HelpCommand::getName() const {
    return "help";
}

void DumpCommand::execute(Game& game, std::istream& args) const {
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

std::string DumpCommand::getName() const {
    return "dump";
}

void ExitCommand::execute(Game& game, std::istream& args) const {
    game.running = false;
}

std::string ExitCommand::getName() const {
    return "exit";
}

void LoadCommand::execute(Game& game, std::istream& args) const {
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

std::string LoadCommand::getName() const {
    return "load";
}

void ClearCommand::execute(Game& game, std::istream& args) const {
    game.engine.clear();
    std::cout << "Universe cleared" << std::endl;
    game.showStatus();
}

std::string ClearCommand::getName() const {
    return "clear";
}

void StatusCommand::execute(Game& game, std::istream& args) const {
    game.showStatus();
}

std::string StatusCommand::getName() const {
    return "status";
}

void RuleCommand::execute(Game& game, std::istream& args) const {
    std::string ruleString;
    if (args >> ruleString) {
        game.engine.setRule(ruleString);
        std::cout << "Rule changed to: " << game.engine.getStringRule() << std::endl;
    } else {
        std::cout << "Current rule: " << game.engine.getStringRule() << std::endl;
    }
}

std::string RuleCommand::getName() const {
    return "rule";
}
