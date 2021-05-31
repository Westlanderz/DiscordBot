#ifndef help_hpp
#define help_hpp

#include "../command.hpp"

class Help : public Command {
    private:
        std::vector<std::string> names;
        Module *module;

    public:
        Help(std::vector<std::string>);

        virtual std::string getHelpMessage() override;
        virtual void execute(dpp::Message) override;
};

#endif
