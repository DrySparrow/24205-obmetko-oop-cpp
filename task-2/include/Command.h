#include <string>
#include "game.h"

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(Game& game, std::istream& args) const = 0;
    virtual std::string getName() const = 0;
};
