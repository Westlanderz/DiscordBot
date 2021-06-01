#ifndef help_hpp
#define help_hpp

#include "../command.hpp"

class Help : public Command {
    public:
        Help(std::vector<std::string>);
        std::string getHelpMessage();
        void execute(dpp::Message);
};

#endif
