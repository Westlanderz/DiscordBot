#ifndef CONTACT_HPP
#define CONTACT_HPP

#include "../command.hpp"

class Contact : public Command {
    public:
        Contact(std::vector<std::string>);
        std::string getHelpMessage();
        void execute(dpp::Message);
        bool hasPermsToRun(dpp::User) override;
};

#endif // CONTACT_HPP
