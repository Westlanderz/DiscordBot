#include "../include/bot.hpp"
#include "../include/commandhandler.hpp"

std::shared_ptr<DppBot> newBot(){
    return std::make_shared<DppBot>();
}

Bot::Bot(std::string name, std::string prefix): username{name}, defaultPrefix{prefix} {
    bot = newBot();
    botOwnerRole = "asdasdasd";
    bot->prefix = prefix;
    bot->debugUnhandled = false;
}

void Bot::login(std::string token) {
    std::shared_ptr<asio::io_context> aioc = std::make_shared<asio::io_context>();
    bot->initBot(6, token, aioc);
}

void Bot::setIntents(uint16_t intents) {
    bot->intents = intents;
}

void Bot::initServerJoiner() {
    bot->handleGUILD_CREATE([this](dpp::Guild guild) {
        addCommandHandler(this, guild);
    });
}

void Bot::initHandlers() {
    bot->handleREADY([this](json data) { self = data["user"]; std::cout << "Connected to the servers" << std::endl;});
    bot->handleMESSAGE_CREATE([this](dpp::Message msg) {
        dpp::User author = *msg.author;
        if(author["id"] == self["id"]) {
            return;
        }
        auto handler = this->isCommandHandler(*msg.guild_id->get());
        if(handler != nullptr)
            handler->handleMessage(msg);
        else 
            this->sendMessage(*msg.channel_id, "WTF this server does not have a handler contact SenpaiR6#1717");
    });
}

void Bot::run() {
    bot->run();
}

CommandHandler * Bot::isCommandHandler(const dpp::snowflake guild_id) {
    for(auto it = commandhandlers.begin(); it != commandhandlers.end(); it++) {
        if(it->first["id"] == std::to_string(guild_id)) {
            return it->second;
        }
    }
    return nullptr;
}

std::shared_ptr<DppBot> Bot::hasDpp() {
    return bot;
}

std::string Bot::isPrefix() {
    return defaultPrefix;
}

void Bot::addCommandHandler(Bot *bot, dpp::Guild guild) {
    commandhandlers.insert(std::pair<dpp::Guild, CommandHandler *>(guild, new CommandHandler(bot, guild, defaultPrefix)));
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

void Bot::sendMessage(const dpp::snowflake channelid, std::string message) {
    bot->createMessage()
        ->channel_id(channelid)
        ->content(message)
        ->run();
}

void Bot::sendMessage(dpp::User user, std::string message) {
    bot->createDM()
        ->recipient_id(user["id"])
        ->run();
}
