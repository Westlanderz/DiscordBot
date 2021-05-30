#include "../include/bot.hpp"

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
    bot->handleGUILD_CREATE();
}

void Bot::initModules() {

}

void Bot::run() {
    bot->run();
}

CommandHandler * Bot::isCommandHandler(dpp::Guild guild) {

}

DppBot * Bot::hasDpp() {
    return bot;
}

std::string Bot::isPrefix() {
    return defaultPrefix;
}

void Bot::addCommandHandler(dpp::Guild guild) {
    commandhandlers.push_back(std::pair<dpp::Guild, CommandHandler *>(guild, new CommandHandler()))
}

void Bot::removeCommandHandler(dpp::Guild guild) {
    delete commandhandlers.at(guild);
    std::map<dpp::Guild, CommandHandler *>::iterator remove = nullptr;
    for(auto it = commandhandlers.begin(); it != commandhandlers.end(); it++) {
        if(*it->first == guild)
            remove = it;
    }
    commandhandlers.erase(remove);
}

void Bot::sendMessage(dpp::snowflake channelid) {
    
}

void Bot::sendMessage(dpp::User user) {
    
}
