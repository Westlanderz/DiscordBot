#ifndef commandhandler_hpp
#define commandhandler_hpp

#include "include.hpp"
#include <vector>

class Bot;
class Module;
class Command;

class CommandHandler {
    private:
        Bot *bot;
        dpp::Guild guild;
        std::string prefix;
        std::vector<Module *> modules;
        dpp::Role adminRole;
        dpp::Role modRole;

    public:
        CommandHandler(Bot *, dpp::Guild, std::string, std::vector<Module *>);
        virtual ~CommandHandler();

        void initHandlers();
        void initDefault();
        void handleMessage(dpp::Message);
        void loadModule(Module *);
        void unloadModule(Module *);
        std::vector<Command *> getCommands();
        void newPrefix(std::string);
        std::string isPrefix();
        bool isCommand(dpp::Message);
        dpp::Guild isFromGuild();
        void addModRole(dpp::Role);
        void removeModRole(dpp::Role);
        void addAdminRole(dpp::Role);
        void removeAdminRole(dpp::Role);
        dpp::Role modRole();
        dpp::Role adminRole();
};

#endif
