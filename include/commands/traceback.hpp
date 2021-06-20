#ifndef __TRACEBACK_H__
#define __TRACEBACK_H__

#include "../command.hpp"

namespace bot {
    class Traceback : public Command {
        public:
            Traceback(std::vector<std::string>);
            std::string getHelpMessage();
            void execute(dpp::Message);
            bool hasPermsToRun(dpp::User) override;
    };
}

#endif // __TRACEBACK_H__