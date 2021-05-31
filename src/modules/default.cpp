#include "../../include/modules/default.hpp"

Default::Default(std::string name, CommandHandler *handler, std::vector<Command *> command): Module(name, handler, command) {}
