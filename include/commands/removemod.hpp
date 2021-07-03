#ifndef REMOVEMOD_HPP
#define REMOVEMOD_HPP

#include "../command.hpp"

class RemoveMod : public Command {
    public:
        RemoveMod(std::vector<std::string>);
        std::string getHelpMessage();
        void execute(dpp::Message);
        bool hasPermsToRun(dpp::User) override;
};


#endif // REMOVEMOD_HPP
