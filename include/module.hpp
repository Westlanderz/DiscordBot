#ifndef module_hpp
#define module_hpp

#include <vector>
#include <string>
#include <iostream>

#include "command.hpp"

class CommandHandler;

class Module {
    private:
        std::string name;
        std::vector<Command *> includedCommands;
        bool loaded;
        CommandHandler *commandHandler;

    public:
        Module(std::string name, CommandHandler *commandHandler, std::vector<Command *> includedCommands) {
            this->name = name;
            this->commandHandler = commandHandler;
            this->includedCommands = includedCommands;
        };
        virtual ~Module() {
            for(auto &command : this->includedCommands) {
                delete command;
            }
        };

        virtual std::string isName() { return name; };
        virtual std::vector<Command *> commands() { return includedCommands; };
        virtual bool isLoaded() { return loaded; };
        virtual void load() { loaded = true; };
        virtual void unload() { loaded = false; };
        virtual CommandHandler * isHandler() { return commandHandler; };
};

#endif