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
        std::vector<dpp::Role> adminRole;
        std::vector<dpp::Role> modRole;

    public:
        CommandHandler(Bot *, dpp::Guild, std::string);
        virtual ~CommandHandler() = default;

        void initDefault();
        void handleMessage(dpp::Message);
        void loadModule(Module *);
        void unloadModule(Module *);
        std::vector<Command *> getCommands();
        void newPrefix(std::string);
        std::string isPrefix();
        bool isCommand(std::string);
        dpp::Guild isFromGuild();
        void addModRole(dpp::Role);
        void removeModRole(dpp::Role);
        void addAdminRole(dpp::Role);
        void removeAdminRole(dpp::Role);
        std::vector<dpp::Role> modRoles();
        std::vector<dpp::Role> adminRoles();
        Bot * hasBot();
};

#endif
