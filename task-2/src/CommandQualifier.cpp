#ifndef COMMAND_QUALIFIER_H
#define COMMAND_QUALIFIER_H

#include "Commands.cpp"
#include <memory>
#include <string>
#include <unordered_map>

class CommandQualifier {
private:
    std::unordered_map<std::string, std::shared_ptr<Command>> commandMap;
    std::unordered_map<std::string, std::string> aliases;
    
    void initializeCommands() {
        registerCommand(std::make_shared<TickCommand>());
        registerCommand(std::make_shared<HelpCommand>());
        registerCommand(std::make_shared<DumpCommand>());
        registerCommand(std::make_shared<ExitCommand>());
        registerCommand(std::make_shared<LoadCommand>());
        registerCommand(std::make_shared<ClearCommand>());
        registerCommand(std::make_shared<StatusCommand>());
        registerCommand(std::make_shared<RuleCommand>());
        
        registerAlias("t", "tick");
        registerAlias("h", "help");
        registerAlias("quit", "exit");
        registerAlias("q", "exit");
        registerAlias("save", "dump");
    }
    
    void registerCommand(std::shared_ptr<Command> cmd) {
        commandMap[cmd->getName()] = cmd;
    }
    
    void registerAlias(const std::string& alias, const std::string& commandName) {
        aliases[alias] = commandName;
    }
    
public:
    CommandQualifier() {
        initializeCommands();
    }
    
    std::shared_ptr<Command> qualifyCommand(const std::string& commandName) const {
        auto it = commandMap.find(commandName);
        if (it != commandMap.end()) {
            return it->second;
        }
        
        auto aliasIt = aliases.find(commandName);
        if (aliasIt != aliases.end()) {
            return commandMap.at(aliasIt->second);
        }
        
        return nullptr;
    }
    
    void executeCommand(Game& game, const std::string& commandLine) const {
        std::stringstream ss(commandLine);
        std::string commandName;
        ss >> commandName;
        
        if (commandName.empty()) return;
        
        auto command = qualifyCommand(commandName);
        if (command) {
            command->execute(game, ss);
        } else {
            std::cout << "Unknown command: " << commandName << std::endl;
            std::cout << "Type 'help' for available commands" << std::endl;
        }
    }
    
    std::vector<std::shared_ptr<Command>> getAllCommands() const {
        std::vector<std::shared_ptr<Command>> result;
        for (const auto& pair : commandMap) {
            result.push_back(pair.second);
        }
        return result;
    }
    
    std::vector<std::string> getAliasesForCommand(const std::string& commandName) const {
        std::vector<std::string> result;
        for (const auto& pair : aliases) {
            if (pair.second == commandName) {
                result.push_back(pair.first);
            }
        }
        return result;
    }
};

#endif
