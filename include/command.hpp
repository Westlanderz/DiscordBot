#ifndef command_hpp
#define command_hpp

#include "include.hpp"

class Module;

class Command {
    private:
        std::vector<std::string> names;
        Module *module;

    public:
        Command(std::vector<std::string> names, Module *module) {
            this->names = names;
            this->module = module;
        }
        virtual ~Command() = default;

        virtual std::string getHelpMessage() = 0;
        virtual void execute(dpp::Message) = 0;
        virtual bool hasPermsToRun(dpp::User user = NULL) { return true; };
        virtual bool isName(std::string name = "") {
            if(!name.compare("")) {
                name = names.at(0);
            }
            for(auto it = names.begin(); it != names.end(); it++) {
                if(!it->compare(name))
                    return true;
            }
            return false;
        };
        virtual Module * isModule() { return module; };
        virtual std::string getName() { return names.at(0); };
};

#endif