#ifndef COMMAND_QUALIFIER_H
#define COMMAND_QUALIFIER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// Forward declarations
class Command;
class Game;

class CommandQualifier {
private:
    std::unordered_map<std::string, std::shared_ptr<Command>> commandMap;
    std::unordered_map<std::string, std::string> aliases;
    
    // Вспомогательные методы
    void initializeCommands();
    void registerCommand(std::shared_ptr<Command> cmd);
    void registerAlias(const std::string& alias, const std::string& commandName);
    
public:
    CommandQualifier();
    
    // Основные публичные методы
    std::shared_ptr<Command> qualifyCommand(const std::string& commandName) const;
    void executeCommand(Game& game, const std::string& commandLine) const;
    
    std::vector<std::shared_ptr<Command>> getAllCommands() const;
    std::vector<std::string> getAliasesForCommand(const std::string& commandName) const;
};

#endif
