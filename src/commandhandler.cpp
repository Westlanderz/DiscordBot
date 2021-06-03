#include "../include/commandhandler.hpp"
#include "../include/bot.hpp"
#include "../include/module.hpp"
#include "../include/commandexception.hpp"

#include "../include/modules/default.hpp"

#include "../include/commands/help.hpp"
#include "../include/commands/uptime.hpp"
#include "../include/commands/traceback.hpp"
#include "../include/commands/load.hpp"

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
    commands.push_back(new Load(names));
    // names.clear();
    // names.push_back("help");
    // commands.push_back();
    // names.clear();
    // names.push_back("help");
    // commands.push_back();
    // names.clear();
    // names.push_back("help");
    // commands.push_back();
    // names.clear();
    // names.push_back("help");
    // commands.push_back();
    // names.clear();
    auto default_module = new Default("default", this, commands);
    this->loadModule(default_module);
    modules.push_back(default_module);
    for(auto &command : commands) {
        command->addToModule(default_module);
    }
    commands.clear();
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
    std::string content = *msg.content.get();
    Command *command = this->isCommand(content);
    dpp::User author = *msg.author.get();
    if(command != nullptr && command->hasPermsToRun(author)) {
        command->execute(msg);
    }
}

void CommandHandler::loadModule(Module *module) {
    module->load();
}

void CommandHandler::unloadModule(Module *module) {
    module->unload();
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
