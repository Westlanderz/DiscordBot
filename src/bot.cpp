#include "../include/bot.hpp"
#include "../include/commandhandler.hpp"

std::shared_ptr<DppBot> newBot(){
    return std::make_shared<DppBot>();
}

Bot::Bot(std::string name, std::string prefix): username{name}, defaultPrefix{prefix} {
    bot = newBot();
    botOwnerRole = "owner_YAGPDB2U";
    bot->prefix = prefix;
    bot->debugUnhandled = false;
    starttime = std::chrono::high_resolution_clock::now();
}

Bot::~Bot() {
    for(auto &handler : this->commandhandlers) {
        delete handler.second;
    }
    this->commandhandlers.clear();
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
        this->addCommandHandler(this, guild);
    });
}

void Bot::initHandlers() {
    bot->handleREADY([this](json data) { self = data["user"]; std::cout << "\033[1;35mConnected to the servers\033[0m" << std::endl;});
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
    bot->handleGUILD_DELETE([this](dpp::Guild guild) {
        this->removeCommandHandler(guild);
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

void Bot::sendMessage(const dpp::snowflake channelid, dpp::MessageEmbed embed) {
    bot->createMessage()
        ->channel_id(channelid)
        ->embed(embed.getEmbed())
        ->run();
}

double Bot::uptime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto time_now = std::chrono::high_resolution_clock::to_time_t(now);
    auto time_start = std::chrono::high_resolution_clock::to_time_t(starttime);
    return std::difftime(time_now, time_start);
}
