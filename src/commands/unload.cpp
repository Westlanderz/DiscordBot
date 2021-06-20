#include "../../include/commands/unload.hpp"
#include "../../include/module.hpp"
#include "../../include/commandhandler.hpp"
#include "../../include/bot.hpp"
#include "../../include/commandexception.hpp"

using namespace bot;

UnLoad::UnLoad(std::vector<std::string> names): Command(names) {}

std::string UnLoad::getHelpMessage() {
    return "Use " + module->isHandler()->isPrefix() + names[0] + " <module> to unload that module.";
}

void UnLoad::execute(dpp::Message msg) {
    try {
        CommandHandler *handler = module->isHandler();
        Bot *bot = handler->hasBot();
        std::size_t find_args = msg.content->find(" ");
        std::size_t find_command = msg.content->find(" ", find_args + 1);
        std::string module_name = "";
        std::string unload_msg = "";
        std::vector<Module *> modules = handler->getModules();
        if(find_args != std::string::npos) {
            if(find_command != std::string::npos) {
                module_name = msg.content->substr(find_args + 1, find_command - find_args);
            } else {
                module_name = msg.content->substr(find_args + 1);
            }
            if(!module_name.compare("core"))
                throw CommandException("Can not unload " + module_name, EXECUTE_ERROR, 0);
            unload_msg = "Unable to find this module or this module is not yet loaded. These are the current loaded modules: ";
            for(auto &_module : modules) {
                if(_module->isName(module_name) && _module->isLoaded() && _module->getName().compare("core")) {
                    handler->unloadModule(_module);
                    bot->sendMessage(*msg.channel_id, false, "Unloaded the " + _module->getName() + " module for you.");
                    std::cout << "\033[1;32mExecuted " + this->getName() + "\033[0m" << std::endl;
                    return;
                } else {
                    if(_module->isLoaded() && _module->getName().compare("core")) {
                        unload_msg.append(_module->getName());
                        if(!_module->getName().compare(modules.at(modules.size() - 1)->getName()))
                            unload_msg.append(". ");
                        else
                            unload_msg.append(", ");
                    } else
                        unload_msg.append(". ");
                }
            }
            bot->sendMessage(*msg.channel_id, false, unload_msg);
            throw CommandException("Could not execute " + this->getName(), EXECUTE_ERROR, 0);
        } else {
            unload_msg = "You have not given a module to unload. Please select one of the following modules to unload: ";
            for(auto &_module : modules) {
                if(_module->isLoaded() && _module->getName().compare("core")) {
                    unload_msg.append(_module->getName());
                    if(!_module->getName().compare(modules.at(modules.size() - 1)->getName()))
                        unload_msg.append(". ");
                    else
                        unload_msg.append(", ");
                } else
                    unload_msg.append(". ");
            }
            bot->sendMessage(*msg.channel_id, false, unload_msg + this->getHelpMessage());
            throw CommandException("Could not execute " + this->getName(), PARAM_ERROR, 0);
        }
    } catch(CommandException &e) {
        std::cerr << "\033[1;31m" << e.what() << " \033[1;35mwith error code \033[1;36m" << e.getErrorNumber() << " \033[0m" << std::endl;
        module->isHandler()->setLastException(&e);
    }
}

bool UnLoad::hasPermsToRun(dpp::User user) {
    std::vector<dpp::snowflake> admin = module->isHandler()->adminRoles();
    std::vector<Module *> modules = module->isHandler()->getModules();
    dpp::Guild guild = module->isHandler()->isFromGuild();
    bool isAdmin = false;
    std::string authorid = user["id"].get<std::string>();
    std::string compareUser = user["username"].get<std::string>()
                .append("#")
                .append(user["discriminator"].get<std::string>());
    if(module->isHandler()->hasBot()->isOwner(compareUser))
        return true;
    for(std::size_t i = 0; i < guild.at(0)["members"].size(); ++i) {
        if(guild.at(0)["members"].at(i)["user"]["id"] == authorid){
            for(std::size_t j = 0; j < guild.at(0)["members"].at(i)["roles"].size(); ++j) {
                for(auto &role : admin) {
                    if(guild.at(0)["members"].at(i)["roles"].at(j) == std::to_string(role))
                        isAdmin = true;
                }
            }
        }
    }
    std::cout << (isAdmin ? "\033[1;32mPermission granted\033[0m" : "\033[1;31mNot enough permissions\033[0m")<< std::endl;
    return isAdmin;
}
