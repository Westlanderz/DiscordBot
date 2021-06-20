#ifndef module_hpp
#define module_hpp

#include <vector>
#include <string>
#include <iostream>

#include "command.hpp"

namespace bot {
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

            virtual std::string getName() { return name; };
            virtual bool isName(std::string name) {
                if(!this->name.compare(name))
                        return true;
                return false;
            };
            virtual std::vector<Command *> commands() { return includedCommands; };
            virtual bool isLoaded() { return loaded; };
            virtual void load() { loaded = true; };
            virtual void unload() { loaded = false; };
            virtual CommandHandler * isHandler() { return commandHandler; };
    };
}

#endif