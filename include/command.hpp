#ifndef command_hpp
#define command_hpp

#include "include.hpp"

class Module;

class Command {
    private:
        std::vector<std::string> names;
        Module *module;

    public:
        Command(std::vector<std::string> names) {
            this->names = names;
        }
        virtual ~Command() = default;

        virtual std::string getHelpMessage();
        virtual void execute(dpp::Message);
        virtual bool hasPermsToRun(dpp::User) { return true; };
        virtual bool isName(std::string name) {
            for(auto it = names.begin(); it != names.end(); it++) {
                if(!it->compare(name))
                    return true;
            }
            return false;
        };
};

#endif