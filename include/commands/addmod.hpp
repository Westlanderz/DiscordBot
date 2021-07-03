#ifndef ADDMOD_HPP
#define ADDMOD_HPP

#include "../command.hpp"

class AddMod : public Command {
    public:
        AddMod(std::vector<std::string>);
        std::string getHelpMessage();
        void execute(dpp::Message);
        bool hasPermsToRun(dpp::User) override;
};

#endif // ADDMOD_HPP
