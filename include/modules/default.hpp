#ifndef default_hpp
#define default_hpp

#include "../module.hpp"

class Default : public Module {
    private:
        std::string name;
        std::vector<Command *> includedCommands;
        bool loaded;
        CommandHandler *commandHandler;

    public:
        Default(std::string, CommandHandler *, std::vector<Command *>);

};

#endif
