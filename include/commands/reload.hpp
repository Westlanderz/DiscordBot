#ifndef RELOAD_HPP
#define RELOAD_HPP

#include "../command.hpp"

namespace bot {
    class Reload : public Command {
        public:
            Reload(std::vector<std::string>);
            std::string getHelpMessage();
            void execute(dpp::Message);
            bool hasPermsToRun(dpp::User) override;
    };
}

#endif // RELOAD_HPP
