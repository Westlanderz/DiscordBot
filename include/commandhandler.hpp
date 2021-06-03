#ifndef commandhandler_hpp
#define commandhandler_hpp

#include "include.hpp"
#include <vector>

class Bot;
class Module;
class Command;
class CommandException;

class CommandHandler {
    private:
        Bot *bot;
        dpp::Guild guild;
        std::string prefix;
        std::vector<Module *> modules;
        std::vector<dpp::snowflake> adminRole;
        std::vector<dpp::snowflake> modRole;
        CommandException *lastException;

    public:
        CommandHandler(Bot *, dpp::Guild, std::string);
        virtual ~CommandHandler();

        void initDefault();
        void handleMessage(dpp::Message);
        void loadModule(Module *);
        void unloadModule(Module *);
        std::vector<Module *> getModules();
        std::vector<Command *> getCommands();
        void newPrefix(std::string);
        std::string isPrefix();
        Command * isCommand(std::string);
        dpp::Guild isFromGuild();
        void addModRole(const dpp::snowflake);
        void removeModRole(const dpp::snowflake);
        void addAdminRole(const dpp::snowflake);
        void removeAdminRole(const dpp::snowflake);
        std::vector<dpp::snowflake> modRoles();
        std::vector<dpp::snowflake> adminRoles();
        Bot * hasBot();
        CommandException * getLastException();
        void setLastException(CommandException *);
};

#endif
