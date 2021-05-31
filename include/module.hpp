#ifndef module_hpp
#define module_hpp

#include <vector>
#include <string>

class CommandHandler;
class Command;

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
        virtual ~Module() = default;

        virtual std::string isName() { return name; };
        virtual std::vector<Command *> commands() { return includedCommands; };
        virtual bool isLoaded() { return loaded; };
        virtual void load() { loaded = true; };
        virtual void unload() { loaded = false; };
        virtual CommandHandler * isHandler() { return commandHandler; };
};

#endif