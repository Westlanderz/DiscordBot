#ifndef command_hpp
#define command_hpp

#include "include.hpp"

class Module;

class Command {
    protected:
        std::vector<std::string> names;
        Module *module;

    public:
        Command(std::vector<std::string> names) {
            this->names = names;
        };
        virtual ~Command() = default;

        virtual std::string getHelpMessage() = 0;
        virtual void execute(dpp::Message) = 0;
        virtual bool hasPermsToRun(dpp::User user = NULL) { return true; };
        virtual bool isName(std::string name) {
            for(auto &_name : names) {
                if(!_name.compare(name))
                    return true;
            }
            return false;
        };
        virtual Module * isModule() { return module; };
        virtual std::string getName() { return names.at(0); };
        virtual void addToModule(Module *module) { this->module = module; };
};

#endif