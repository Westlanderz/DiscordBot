#ifndef ADDADMIN_HPP
#define ADDADMIN_HPP

#include "../command.hpp"

namespace bot {
    class AddAdmin : public Command {
        public:
            AddAdmin(std::vector<std::string>);
            std::string getHelpMessage();
            void execute(dpp::Message);
            bool hasPermsToRun(dpp::User) override;
    };
}

#endif // ADDADMIN_HPP
