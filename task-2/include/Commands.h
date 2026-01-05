#ifndef COMMANDS_H
#define COMMANDS_H

#include "Command.h"
#include <string>
#include <iostream>

class Game;
class GameOfLifeEngine;

class TickCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override;
    std::string getName() const override;
};

class HelpCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override;
    std::string getName() const override;
};

class DumpCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override;
    std::string getName() const override;
};

class ExitCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override;
    std::string getName() const override;
};

class LoadCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override;
    std::string getName() const override;
};

class ClearCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override;
    std::string getName() const override;
};

class StatusCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override;
    std::string getName() const override;
};

class RuleCommand : public Command {
public:
    void execute(Game& game, std::istream& args) const override;
    std::string getName() const override;
};

#endif