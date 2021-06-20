#ifndef REMOVEADMIN_HPP
#define REMOVEADMIN_HPP

#include "../command.hpp"

namespace bot {
    class RemoveAdmin : public Command {
        public:
            RemoveAdmin(std::vector<std::string>);
            std::string getHelpMessage();
            void execute(dpp::Message);
            bool hasPermsToRun(dpp::User) override;
    };
}

#endif // REMOVEADMIN_HPP
