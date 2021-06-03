#ifndef UNLOAD_HPP
#define UNLOAD_HPP

#include "../command.hpp"

class UnLoad : public Command {
    public:
        UnLoad(std::vector<std::string>);
        std::string getHelpMessage();
        void execute(dpp::Message);
        bool hasPermsToRun(dpp::User) override;
};

#endif // UNLOAD_HPP
