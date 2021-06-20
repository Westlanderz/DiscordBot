#include <fstream>

#include "../include/commandhandler.hpp"
#include "../include/bot.hpp"
#include "../include/module.hpp"
#include "../include/commandexception.hpp"

#include "../include/modules/core.hpp"

#include "../include/commands/help.hpp"
#include "../include/commands/uptime.hpp"
#include "../include/commands/traceback.hpp"
#include "../include/commands/load.hpp"
#include "../include/commands/unload.hpp"
#include "../include/commands/addadmin.hpp"
#include "../include/commands/reload.hpp"

using namespace bot;

CommandHandler::CommandHandler(Bot *bots, dpp::Guild guilds, std::string defaultPrefix): bot{bots}, guild{guilds}, prefix{defaultPrefix} {
    std::vector<Command *> commands;
    std::vector<std::string> names;
    //TODO: this block for every module
    //TODO: list commands here
    names.push_back("help");
    commands.push_back(new Help(names));
    names.clear();
    names.push_back("uptime");
    commands.push_back(new Uptime(names));
    names.clear();
    names.push_back("traceback");
    names.push_back("trace");
    commands.push_back(new Traceback(names));
    names.clear();
    names.push_back("load");
    names.push_back("l");
    commands.push_back(new Load(names));
    names.clear();
    names.push_back("unload");
    names.push_back("ul");
    commands.push_back(new UnLoad(names));
    names.clear();
    names.push_back("addadmin");
    commands.push_back(new AddAdmin(names));
    names.clear();
    names.push_back("reload");
    names.push_back("rl");
    commands.push_back(new Reload(names));
    // names.clear();
    // names.push_back("help");
    // commands.push_back();
    // names.clear();
    auto default_module = new Core("core", this, commands);
    this->loadModule(default_module);
    modules.push_back(default_module);
    for(auto &command : commands) {
        command->addToModule(default_module);
    }
    commands.clear();
    std::string loading{""};
    for(auto &guild : bot->config["guild_settings"]) {
        if(guild["id"] == this->guild.at(0)["id"]) {
            for(auto &module : guild["loadedModules"]) {
                loading = module.get<std::string>();
                for(auto &load : modules) {
                    if(loading.compare(load->getName()))
                        this->loadModule(load);
                }
            }
            //TODO: load admin roles at reload
            break;
        }
    }
}

CommandHandler::~CommandHandler() {
    for(auto &module : modules) {
        delete module;
    }
}

void CommandHandler::initDefault() {
    loadModule(modules.at(0));
}

void CommandHandler::handleMessage(dpp::Message msg) {
    try {
        std::string content = *msg.content.get();
        Command *command = this->isCommand(content);
        dpp::User author = *msg.author.get();
        if(command != nullptr && command->hasPermsToRun(author)) {
            command->execute(msg);
        } else if(command != nullptr && !command->hasPermsToRun(author)) {
            bot->sendMessage(*msg.channel_id.get(), false, "You do not have the permission to run this command");
            throw CommandException("Not enough permissions to run this " + command->getName(), PERMISSION_ERROR, 0);
        } else if(command == nullptr && content.starts_with(prefix)) {
            bot->sendMessage(*msg.channel_id.get(), false, "I cannot find this command, this is either not a command or the module with that command is not loaded yet.");
            throw CommandException("This is not a known command", EXECUTE_ERROR, 0);
        }
    } catch(CommandException &e) {
        std::cerr << "\033[1;31m" << e.what() << " \033[0m" << std::endl;
    }
}

void CommandHandler::loadModule(Module *module) {
    module->load();
    auto config = bot->config;
    for(std::size_t i = 0; i < config["guild_settings"].size(); ++i) {
        if(config["guild_settings"].at(i)["id"] == this->guild.at(0)["id"]) {
            bool found = false;
            for(std::size_t j = 0; j < config["guild_settings"].at(i)["loadedModules"].size(); ++j) {
                if(!config["guild_settings"].at(i)["loadedModules"].at(j).get<std::string>().compare(module->getName())) {
                    found = true;
                    break;
                }
            }
            if(!found)
                config["guild_settings"].at(i)["loadedModules"].push_back(module->getName());
            break;
        }
    }
    bot->updateConfigFile(config);
}

void CommandHandler::unloadModule(Module *module) {
    module->unload();
    auto config = bot->config;
    for(std::size_t i = 0; i < config["guild_settings"].size(); ++i) {
        if(config["guild_settings"].at(i)["id"] == this->guild.at(0)["id"]) {
            for(std::size_t j = 0; j < config["guild_settings"].at(i)["loadedModules"].size(); ++j) {
                if(!config["guild_settings"].at(i)["loadedModules"].at(j).get<std::string>().compare(module->getName())) {
                    config["guild_settings"].at(i)["loadedModules"].erase(j);
                    break;
                }
            }
            break;
        }
    }
    bot->updateConfigFile(config);
}

std::vector<Module *> CommandHandler::getModules() {
    return modules;
}

std::vector<Command *> CommandHandler::getCommands() {
    std::vector<Command *> loadedCommands, commands;
    for(auto &_module : modules) {
        if(_module->isLoaded()) {
            commands = _module->commands();
            for(auto loaded = commands.begin(); loaded != commands.end(); loaded++) {
                loadedCommands.push_back(*loaded);
            }
        }
    }
    return loadedCommands;
}

void CommandHandler::newPrefix(std::string prefix) {
    this->prefix = prefix;
    dpp::json config = bot->config;
    for(std::size_t i = 0; i < config["guild_settings"].size(); ++i) {
        if(config["guild_settings"].at(i)["id"] == this->guild.at(0)["id"]) {
            config["guild_settings"].at(i)["prefix"] = prefix;
            break;
        }
    }
    bot->updateConfigFile(config);
}

std::string CommandHandler::isPrefix() {
    return prefix;
}

Command * CommandHandler::isCommand(std::string msg) {
    std::size_t command = msg.find(" ");
    std::string to_find;
    std::vector<Command *> loadedCommands;
    if(command != std::string::npos && msg.starts_with(prefix)) {
        to_find = msg.substr(bot->isPrefix().length(), command - 1);
        loadedCommands = this->getCommands();
        for(auto &command : loadedCommands) {
            if(command->isName(to_find))
                return command;
        }
    } else if(msg.starts_with(prefix)) {
        to_find = msg.substr(bot->isPrefix().length());
        loadedCommands = this->getCommands();
        for(auto &command : loadedCommands) {
            if(command->isName(to_find))
                return command;
        }
    }
    return nullptr;
}

dpp::Guild CommandHandler::isFromGuild() {
    return guild;
}

void CommandHandler::addModRole(const dpp::snowflake id) {
    modRole.push_back(id);
}

void CommandHandler::removeModRole(const dpp::snowflake id) {
    auto remove = modRole.end();
    for(auto it = modRole.begin(); it != modRole.end(); it++) {
        if(*it == id)
            remove = it;
    }
    if(remove != modRole.end())
        modRole.erase(remove);
}

void CommandHandler::addAdminRole(const dpp::snowflake id) {
    adminRole.push_back(id);
}

void CommandHandler::removeAdminRole(const dpp::snowflake id) {
    auto remove = adminRole.end();
    for(auto it = adminRole.begin(); it != adminRole.end(); it++) {
        if(*it == id)
            remove = it;
    }
    if(remove != adminRole.end())
        adminRole.erase(remove);
}

std::vector<dpp::snowflake> CommandHandler::modRoles() {
    return modRole;
}

std::vector<dpp::snowflake> CommandHandler::adminRoles() {
    return adminRole;
}

Bot * CommandHandler::hasBot() {
    return bot;
}

CommandException * CommandHandler::getLastException() {
    return lastException;
}

void CommandHandler::setLastException(CommandException *exception) {
    lastException = exception;
}
