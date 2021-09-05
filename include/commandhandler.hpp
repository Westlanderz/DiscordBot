#ifndef COMMANDHANDLER_HPP
#define COMMANDHANDLER_HPP

#include <vector>

#include "discordpp/constructs/message.hh"

namespace dpp = discordpp;

namespace bot {
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
            std::vector<dpp::Snowflake> adminRole;
            std::vector<dpp::Snowflake> modRole;
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
            void addModRole(const dpp::Snowflake);
            void removeModRole(const dpp::Snowflake);
            void addAdminRole(const dpp::Snowflake);
            void removeAdminRole(const dpp::Snowflake);
            std::vector<dpp::Snowflake> modRoles();
            std::vector<dpp::Snowflake> adminRoles();
            Bot * hasBot();
            CommandException * getLastException();
            void setLastException(CommandException *);
    };
}

#endif // COMMANDHANDLER_HPP
