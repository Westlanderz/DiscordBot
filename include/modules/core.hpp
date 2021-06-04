#ifndef CORE_HPP
#define CORE_HPP

#include "../module.hpp"

class Core : public Module {
    private:
        std::string name;
        std::vector<Command *> includedCommands;
        bool loaded;
        CommandHandler *commandHandler;

    public:
        Core(std::string, CommandHandler *, std::vector<Command *>);

};

#endif // CORE_HPP
