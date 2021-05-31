#include "../include/commandhandler.hpp"
#include "../include/bot.hpp"
#include "../include/module.hpp"
#include "../include/command.hpp"

CommandHandler::CommandHandler(Bot *bots, dpp::Guild guilds, std::string defaultPrefix): bot{bots}, guild{guilds}, prefix{defaultPrefix} {}

void CommandHandler::initDefault() {
    loadModule(modules.at(0));
}

void CommandHandler::handleMessage(dpp::Message msg) {

}

void CommandHandler::loadModule(Module *module) {
    module->load();
}

void CommandHandler::unloadModule(Module *module) {
    module->unload();
}

std::vector<Command *> CommandHandler::getCommands() {
    std::vector<Command *> loadedCommands;
    for(auto it = modules.begin(); it != modules.end(); it++) {
        if((*it)->isLoaded()) {
            for(auto loaded = (*it)->commands().begin(); loaded != (*it)->commands().end(); loaded++)
                loadedCommands.push_back(*loaded);
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

bool CommandHandler::isCommand(std::string msg) {
    std::size_t command = msg.find(" ");
    if(command != std::string::npos) {
        std::string to_find = msg.substr(bot->isPrefix().length(), command);
        for(auto it = modules.begin(); it != modules.end(); it++) {
            for(auto commands = (*it)->commands().begin(); commands != (*it)->commands().end(); commands++) {
                if((*commands)->isName(to_find))
                    return true;
            }
        }
    }
    return false;
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
