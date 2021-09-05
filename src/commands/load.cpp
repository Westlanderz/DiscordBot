#include "../../include/commands/load.hpp"
#include "../../include/module.hpp"
#include "../../include/commandhandler.hpp"
#include "../../include/bot.hpp"
#include "../../include/commandexception.hpp"

using namespace bot;

Load::Load(std::vector<std::string> names): Command(names) {}

std::string Load::getHelpMessage() {
    return "Use " + module->isHandler()->isPrefix() + names[0] + " <module> to load that module and make the commands available.";
}

void Load::execute(dpp::Message msg) {
    try {
        CommandHandler *handler = module->isHandler();
        Bot *bot = handler->hasBot();
        std::size_t find_args = msg.content->find(" ");
        std::size_t find_command = msg.content->find(" ", find_args + 1);
        std::string module_name = "";
        std::string load_msg = "";
        std::vector<Module *> modules = handler->getModules();
        if(find_args != std::string::npos) {
            if(find_command != std::string::npos) {
                module_name = msg.content->substr(find_args + 1, find_command - find_args);
            } else {
                module_name = msg.content->substr(find_args + 1);
            }
            load_msg = "Unable to find this module or this module is already loaded. These are the modules you have not loaded: ";
            for(auto &_module : modules) {
                if(_module->isName(module_name) && !_module->isLoaded()) {
                    handler->loadModule(_module);
                    bot->sendMessage(*msg.channel_id, false, "Loaded the " + _module->getName() + " module for you.");
                    std::cout << "\033[1;32mExecuted " + this->getName() + "\033[0m" << std::endl;
                    return;
                } else {
                    if(!_module->isLoaded()) {
                        load_msg.append(_module->getName());
                        if(!_module->getName().compare(modules.at(modules.size() - 1)->getName()))
                            load_msg.append(". ");
                        else
                            load_msg.append(", ");
                    } else
                        load_msg.append(". ");
                }
            }
            bot->sendMessage(*msg.channel_id, false, load_msg);
            throw CommandException("Could not execute " + this->getName(), EXECUTE_ERROR, 0);
        } else {
            load_msg = "You have not given a module to load. Please select one of the following modules to load: ";
            for(auto &_module : modules) {
                if(!_module->isLoaded()) {
                    load_msg.append(_module->getName());
                    if(!_module->getName().compare(modules.at(modules.size() - 1)->getName()))
                        load_msg.append(". ");
                    else
                        load_msg.append(", ");
                } else
                    load_msg.append(". ");
            }
            bot->sendMessage(*msg.channel_id, false, load_msg);
            throw CommandException("Could not execute " + this->getName(), PARAM_ERROR, 0);
        }
    } catch(CommandException &e) {
        std::cerr << "\033[1;31m" << e.what() << " \033[1;35mwith error code \033[1;36m" << e.getErrorNumber() << " \033[0m" << std::endl;
        module->isHandler()->setLastException(&e);
    }
}

bool Load::hasPermsToRun(dpp::User user) {
    auto handler = module->isHandler();
    std::vector<dpp::Snowflake> admin = handler->adminRoles();
    std::vector<Module *> modules = handler->getModules();
    dpp::Guild guild = handler->isFromGuild();
    bool isAdmin = false;
    std::string authorid = user["id"].get<std::string>();
    std::string compareUser = user["username"].get<std::string>()
                .append("#")
                .append(user["discriminator"].get<std::string>());
    if(handler->hasBot()->isOwner(compareUser))
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
