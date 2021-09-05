#ifndef UPTIME_HPP
#define UPTIME_HPP

#include "../command.hpp"

namespace bot {
    class Uptime : public Command {
        public:
            Uptime(std::vector<std::string>);
            std::string getHelpMessage();
            void execute(dpp::Message);
    };
}

#endif // UPTIME_HPP
