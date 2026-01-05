#include "../include/CommandQualifier.h"
#include "commands.h"
#include "game.h"
#include <iostream>
#include <sstream>

// Вспомогательные приватные методы

void CommandQualifier::initializeCommands() {
    // Регистрация всех команд
    registerCommand(std::make_shared<TickCommand>());
    registerCommand(std::make_shared<HelpCommand>());
    registerCommand(std::make_shared<DumpCommand>());
    registerCommand(std::make_shared<ExitCommand>());
    registerCommand(std::make_shared<LoadCommand>());
    registerCommand(std::make_shared<ClearCommand>());
    registerCommand(std::make_shared<StatusCommand>());
    registerCommand(std::make_shared<RuleCommand>());
    
    // Регистрация алиасов
    registerAlias("t", "tick");
    registerAlias("h", "help");
    registerAlias("quit", "exit");
    registerAlias("q", "exit");
    registerAlias("save", "dump");
}

void CommandQualifier::registerCommand(std::shared_ptr<Command> cmd) {
    commandMap[cmd->getName()] = cmd;
}

void CommandQualifier::registerAlias(const std::string& alias, const std::string& commandName) {
    aliases[alias] = commandName;
}

// Публичные методы

CommandQualifier::CommandQualifier() {
    initializeCommands();
}

std::shared_ptr<Command> CommandQualifier::qualifyCommand(const std::string& commandName) const {
    // Сначала проверяем прямое совпадение
    auto it = commandMap.find(commandName);
    if (it != commandMap.end()) {
        return it->second;
    }
    
    // Затем проверяем алиасы
    auto aliasIt = aliases.find(commandName);
    if (aliasIt != aliases.end()) {
        // Используем at() для безопасного доступа (бросит исключение если не найден)
        return commandMap.at(aliasIt->second);
    }
    
    // Команда не найдена
    return nullptr;
}

void CommandQualifier::executeCommand(Game& game, const std::string& commandLine) const {
    std::stringstream ss(commandLine);
    std::string commandName;
    ss >> commandName;
    
    if (commandName.empty()) return;
    
    auto command = qualifyCommand(commandName);
    if (command) {
        // ПОЛИМОРФНЫЙ ВЫЗОВ: виртуальный метод execute()
        command->execute(game, ss);
    } else {
        std::cout << "Unknown command: " << commandName << std::endl;
        std::cout << "Type 'help' for available commands" << std::endl;
    }
}

std::vector<std::shared_ptr<Command>> CommandQualifier::getAllCommands() const {
    std::vector<std::shared_ptr<Command>> result;
    for (const auto& pair : commandMap) {
        result.push_back(pair.second);
    }
    return result;
}

std::vector<std::string> CommandQualifier::getAliasesForCommand(const std::string& commandName) const {
    std::vector<std::string> result;
    for (const auto& pair : aliases) {
        if (pair.second == commandName) {
            result.push_back(pair.first);
        }
    }
    return result;
}
