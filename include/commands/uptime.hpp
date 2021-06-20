#ifndef uptime_hpp
#define uptime_hpp

#include "../command.hpp"

namespace bot {
    class Uptime : public Command {
        public:
            Uptime(std::vector<std::string>);
            std::string getHelpMessage();
            void execute(dpp::Message);
    };
}

#endif
