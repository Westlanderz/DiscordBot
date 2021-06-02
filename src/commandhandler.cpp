#include "../include/commandhandler.hpp"
#include "../include/bot.hpp"
#include "../include/module.hpp"
#include "../include/command.hpp"

#include "../include/modules/default.hpp"

#include "../include/commands/help.hpp"
#include "../include/commands/uptime.hpp"
#include "../include/commands/traceback.hpp"

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
    // names.clear();
    // names.at(0) = "help";
    // commands.push_back();
    // names.clear();
    // names.at(0) = "help";
    // commands.push_back();
    // names.clear();
    // names.at(0) = "help";
    // commands.push_back();
    // names.clear();
    // names.at(0) = "help";
    // commands.push_back();
    // names.clear();
    // names.at(0) = "help";
    // commands.push_back();
    // names.clear();
    auto default_module = new Default("default", this, commands);
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
    std::string content = *msg.content;
    auto command = this->isCommand(content);
    if(command != nullptr) {
        command->execute(msg);
    } else if(content.starts_with(prefix)) {
        bot->sendMessage(*msg.channel_id, "Could not find the command you were looking for, try " + this->isPrefix() +  "help to get a list of commands.");
    }
}

void CommandHandler::loadModule(Module *module) {
    module->load();
}

void CommandHandler::unloadModule(Module *module) {
    module->unload();
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

void CommandHandler::addModRole(dpp::Role role) {
    modRole.push_back(role);
}

void CommandHandler::removeModRole(dpp::Role role) {
    auto remove = modRole.end();
    for(auto it = modRole.begin(); it != modRole.end(); it++) {
        if(*it == role)
            remove = it;
    }
    if(remove != modRole.end())
        modRole.erase(remove);
}

void CommandHandler::addAdminRole(dpp::Role role) {
    adminRole.push_back(role);
}

void CommandHandler::removeAdminRole(dpp::Role role) {
    auto remove = adminRole.end();
    for(auto it = adminRole.begin(); it != adminRole.end(); it++) {
        if(*it == role)
            remove = it;
    }
    if(remove != adminRole.end())
        adminRole.erase(remove);
}

std::vector<dpp::Role> CommandHandler::modRoles() {
    return modRole;
}

std::vector<dpp::Role> CommandHandler::adminRoles() {
    return adminRole;
}

Bot * CommandHandler::hasBot() {
    return bot;
}
