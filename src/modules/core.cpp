#include "../../include/modules/core.hpp"

Core::Core(std::string name, CommandHandler *handler, std::vector<Command *> command): Module(name, handler, command) {}
