#ifndef BOT_HPP
#define BOT_HPP

#include <vector>
#include <map>
#include <chrono>
#include <string>

#include "discordpp/constructs/todo.hh"
#include "discordpp/alias.hh"
#include "discordpp/MessageEmbed.hh"
#include "discordpp/snowflake.hh"

namespace dpp = discordpp;

namespace bot {
    class CommandHandler;
    class BotInterface;

    class Bot {
        private:
            BotInterface *bot;
            std::string username;
            std::string defaultPrefix;
            std::vector<dpp::Guild> servers;
            std::map<dpp::Guild, CommandHandler *> commandhandlers;
            std::string token;
            std::string botOwnerRole;
            std::vector<std::string> botOwners;
            bool enableReactions;
            std::chrono::_V2::high_resolution_clock::time_point starttime;
        
        public:
            dpp::json self;
            dpp::json config;

            Bot(std::string, std::string);
            virtual ~Bot();

            void login(std::string);
            void setIntents(uint16_t);
            void initServerJoiner();
            void initHandlers();
            void run();
            CommandHandler * isCommandHandler(const dpp::Snowflake);
            BotInterface * hasDpp();
            std::string isPrefix();
            void addCommandHandler(Bot *, dpp::Guild);
            void removeCommandHandler(dpp::Guild);
            void sendMessage(const dpp::Snowflake, bool, std::string);
            void sendMessage(dpp::User, std::string);
            void sendMessage(const dpp::Snowflake, const dpp::MessageEmbed);
            dpp::json getRoles(const dpp::Snowflake);
            double uptime();
            bool isOwner(std::string);
            void updateConfigFile(dpp::json);
    };
}

#endif // BOT_HPP
