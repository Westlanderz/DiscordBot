#include "../include/bot.hpp"
#include "../include/commandhandler.hpp"
#include "../include/botinterface.hpp"

/**
 * @brief Construct a new Bot:: Bot object
 * 
 * @param name a std::string that sets the username
 * @param prefix a std::string that provides the bot with a default prefix to use
 */
Bot::Bot(std::string name, std::string prefix): username{name}, defaultPrefix{prefix} {
    this->bot = new BotInterface();
    botOwnerRole = "owner_YAGPDB2U";
    bot->isDppBot()->prefix = prefix;
    bot->isDppBot()->debugUnhandled = false;
    starttime = std::chrono::high_resolution_clock::now();
    std::ifstream configfile("../config.json");
    this->config = dpp::json::parse(configfile);
    for(std::size_t i = 0; i < config["owners"].size(); ++i)
        this->botOwners.push_back(config["owners"].at(i));
}

/**
 * @brief Destroy the Bot:: Bot object
 * 
 */
Bot::~Bot() {
    for(auto &handler : this->commandhandlers) {
        delete handler.second;
    }
    this->commandhandlers.clear();
}

/**
 * @brief Initialises the bot object
 * 
 * @param token std::string that is the token to login with at discord
 */
void Bot::login(std::string token) {
    std::shared_ptr<asio::io_context> aioc = std::make_shared<asio::io_context>();
    bot->isDppBot()->initBot(6, token, aioc);
}

/**
 * @brief initialises the intents the bot has
 * 
 * @param intents a uint16_t with all the intents in it
 */
void Bot::setIntents(uint16_t intents) {
    bot->isDppBot()->intents = intents;
}

/**
 * @brief initialises the adding of commandhandlers when joining a server
 * 
 */
void Bot::initServerJoiner() {
    bot->isDppBot()->handleGUILD_CREATE([this](dpp::Guild guild) {
        std::cout << "\033[1;35mJoined the server with id \033[1;36m" << guild["id"] << "\033[0m" << std::endl;
        this->addCommandHandler(this, guild);
    });
}

/**
 * @brief initialises all the other handlers like the messagehandler
 * 
 */
void Bot::initHandlers() {
    bot->isDppBot()->handleREADY([this](dpp::json data) { self = data["user"]; std::cout << "\033[1;35mConnected to the servers\033[0m" << std::endl;});
    bot->isDppBot()->handleMESSAGE_CREATE([this](dpp::Message msg) {
        dpp::User author = *msg.author;
        if(author["id"] == self["id"]) {
            std::cout << "\033[1;36mThis message was send by the bot itself, do not respond to it!\033[0m" << std::endl;
            return;
        }
        auto handler = this->isCommandHandler(*msg.guild_id->get());
        if(handler != nullptr)
            handler->handleMessage(msg);
        else
            this->sendMessage(*msg.channel_id, false, "WTF this server does not have a handler contact SenpaiR6#1717");
    });
    bot->isDppBot()->handleGUILD_DELETE([this](dpp::Guild guild) {
        this->removeCommandHandler(guild);
    });
    bot->isDppBot()->handleCHANNEL_CREATE([this](dpp::Channel ch) {
        //std::cout << ch.dump(4) << std::endl;
    });
}

/**
 * @brief runs the bot
 * 
 */
void Bot::run() {
    bot->isDppBot()->run();
}

/**
 * @brief finds the commandhandler that belongs to that guild
 * 
 * @param guild_id a dpp::snowflake that uniquely defines a guild
 * @return CommandHandler* returns the pointer to the handler of the given guild
 */
CommandHandler * Bot::isCommandHandler(const dpp::snowflake guild_id) {
    for(auto it = commandhandlers.begin(); it != commandhandlers.end(); it++) {
        if(it->first["id"] == std::to_string(guild_id)) {
            return it->second;
        }
    }
    return nullptr;
}

/**
 * @brief this gives the bot atribute back to the user
 * 
 * @return std::shared_ptr<DppBot> the bot object
 */
BotInterface * Bot::hasDpp() {
    return bot;
}

/**
 * @brief this checks the default prefix of this bot
 * 
 * @return std::string the default prefix to return
 */
std::string Bot::isPrefix() {
    return defaultPrefix;
}

/**
 * @brief this adds a new commandhandler to this bot and maps it to the given guild
 * 
 * @param bot the bot to link to the commandhandler
 * @param guild the guild to map the new commandhandler to
 */
void Bot::addCommandHandler(Bot *bot, dpp::Guild guild) {
    if(commandhandlers.find(guild) == commandhandlers.end()) {
        std::ifstream configfile("../config.json");
        dpp::json configure = dpp::json::parse(configfile);
        configfile.close();
        bool found = false;
        for(std::size_t i = 0; i < configure["guild_settings"].size(); ++i) {
            if(guild["id"] == configure["guild_settings"].at(i)["id"])
                found = true;
        }
        if(!found) {
            dpp::json newGuild;
            newGuild["id"] = guild["id"];
            newGuild["prefix"] = defaultPrefix;
            newGuild["loadedModules"] = dpp::json::array();
            configure["guild_settings"].push_back(newGuild);
            this->updateConfigFile(configure);
        }
        commandhandlers.insert(std::pair<dpp::Guild, CommandHandler *>(guild, new CommandHandler(bot, guild, defaultPrefix)));
    }
}

/**
 * @brief this removes a commandhandler from the bot
 * 
 * @param guild the guild to remove the commandhandler from
 */
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
    dpp::json configure = config;
    for(std::size_t i = 0; i < configure["guild_settings"].size(); ++i) {
        if(configure["guild_settings"].at(i)["id"] == guild["id"])
            configure["guild_settings"].erase(i);
    }
    this->updateConfigFile(configure);
}

/**
 * @brief This function sends a message to a given channel
 * 
 * @param channelid the channelid to send the message to
 * @param tts this boolean sets if the message should use text-to-speech
 * @param message the message you want to send to the channel
 */
void Bot::sendMessage(const dpp::snowflake channelid, bool tts, std::string message) {
    bot->isDppBot()->createMessage()
        ->channel_id(channelid)
        ->content(message)
        ->tts(tts)
        ->run();
}

/**
 * @brief This function sends a message to a given user
 * 
 * @param user the user object to send the message to
 * @param message the message you want to send
 */
void Bot::sendMessage(dpp::User user, std::string message) {
    bot->isDppBot()->createDM()
        ->recipient_id(dpp::get_snowflake(user["id"]))
        ->onRead([this, message](bool error, dpp::json res) {
            this->sendMessage(dpp::get_snowflake(res["body"]["id"]), false, message);
        })
        ->run();
}

/**
 * @brief This function sends an embeddedmessage to a given channel
 * 
 * @param channelid the channelid to send the message to
 * @param embed the embedded message to send to that channel
 */
void Bot::sendMessage(const dpp::snowflake channelid, dpp::MessageEmbed embed) {
    bot->isDppBot()->createMessage()
        ->channel_id(channelid)
        ->embed(embed.getEmbed())
        ->run();
}

dpp::json Bot::getRoles(const dpp::snowflake guild) {
    bot->isDppBot()->getGuildRoles()
        ->guild_id(guild)
        ->onRead([this](bool error, dpp::json response) {
            return response;
        })
        ->run();
        dpp::json json;
        return json;
}

/**
 * @brief This returns the current uptime of the bot
 * 
 * @return double the uptime of the bot
 */
double Bot::uptime() {
    auto now = std::chrono::high_resolution_clock::now();
    auto time_now = std::chrono::high_resolution_clock::to_time_t(now);
    auto time_start = std::chrono::high_resolution_clock::to_time_t(starttime);
    return std::difftime(time_now, time_start);
}

bool Bot::isOwner(std::string username) {
    for(auto &owner : this->botOwners) {
        if(!owner.compare(username))
            return true;
    }
    return false;
}

void Bot::updateConfigFile(dpp::json configuration) {
    std::ofstream configfile("../config.json");
    configfile << configuration;
    config = configuration;
    configfile.close();
}
