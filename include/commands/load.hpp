#ifndef LOAD_HPP
#define LOAD_HPP

#include "../command.hpp"

class Load : public Command {
    public:
        Load(std::vector<std::string>);
        std::string getHelpMessage();
        void execute(dpp::Message);
        bool hasPermsToRun(dpp::User) override;
};

#endif // LOAD_HPP
