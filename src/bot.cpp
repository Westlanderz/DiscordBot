#include "../include/bot.hpp"
#include "../include/commandhandler.hpp"

Bot::Bot(std::string name, std::string prefix): username{name}, defaultPrefix{prefix} {
    bot = newBot();
    botOwnerRole = "asdasdasd";
    bot->prefix = prefix;
}

void Bot::login(std::string token) {
    std::shared_ptr<asio::io_context> aioc = std::make_shared<asio::io_context>();
    bot->initBot(6, token, aioc);
}

void Bot::setIntents(uint16_t intents) {
    bot->intents = intents;
}

void Bot::initServerJoiner() {
    bot->handleGUILD_CREATE([this](dpp::Guild guild) {});
}

void Bot::initHandlers() {
    bot->handleMESSAGE_CREATE([this](dpp::Message msg) {});
}

void Bot::run() {
    bot->run();
}

CommandHandler * Bot::isCommandHandler(dpp::Guild guild) {
    for(auto it = commandhandlers.begin(); it != commandhandlers.end(); it++) {
        if(it->first == guild)
            return it->second;
    }
}

std::shared_ptr<DppBot> Bot::hasDpp() {
    return bot;
}

std::string Bot::isPrefix() {
    return defaultPrefix;
}

void Bot::addCommandHandler(dpp::Guild guild) {
    commandhandlers.insert(std::pair<dpp::Guild, CommandHandler *>(guild, new CommandHandler(this, guild, defaultPrefix)));
}

void Bot::removeCommandHandler(dpp::Guild guild) {
    std::map<dpp::Guild, CommandHandler *>::iterator remove = commandhandlers.end();
    for(auto it = commandhandlers.begin(); it != commandhandlers.end(); it++) {
        if(it->first == guild) {
            remove = it;
            delete it->second;
        }
    }
    if(remove != commandhandlers.end())
        commandhandlers.erase(remove);
}

void Bot::sendMessage(dpp::snowflake channelid, std::string message) {
    
}

void Bot::sendMessage(dpp::User user, std::string message) {
    
}
