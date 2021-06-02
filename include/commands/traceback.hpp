#ifndef __TRACEBACK_H__
#define __TRACEBACK_H__

#include "../command.hpp"

class Traceback : public Command {
    public:
        Traceback(std::vector<std::string>);
        std::string getHelpMessage();
        void execute(dpp::Message);
};

#endif // __TRACEBACK_H__