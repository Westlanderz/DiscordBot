#ifndef bot_hpp
#define bot_hpp

#include <vector>
#include <map>
#include "include.hpp"

class CommandHandler;

class Bot {
    private:
        std::shared_ptr<DppBot> bot;
        std::string username;
        std::string defaultPrefix;
        std::vector<dpp::Guild> servers;
        std::map<dpp::Guild, CommandHandler *> commandhandlers;
        std::string token;
        std::string botOwnerRole;
        bool enableReactions;
    
    public:
        json self;

        Bot(std::string, std::string);
        virtual ~Bot();

        void login(std::string);
        void setIntents(uint16_t);
        void initServerJoiner();
        void initHandlers();
        void run();
        CommandHandler * isCommandHandler(dpp::Guild);
        std::shared_ptr<DppBot> hasDpp();
        std::string isPrefix();
        void addCommandHandler(dpp::Guild);
        void removeCommandHandler(dpp::Guild);
        void sendMessage(dpp::sptr<const dpp::snowflake>, std::string);
        void sendMessage(dpp::User, std::string);
};

#endif
