#include "../../include/commands/addadmin.hpp"
#include "../../include/module.hpp"
#include "../../include/commandhandler.hpp"
#include "../../include/bot.hpp"
#include "../../include/commandexception.hpp"

#include <algorithm>

using namespace bot;

AddAdmin::AddAdmin(std::vector<std::string> names): Command(names) {}

std::string AddAdmin::getHelpMessage() {
    return "Use " + module->isHandler()->isPrefix() + names[0] + " <role> to add that role to the list of Admin roles.";
}

void AddAdmin::execute(dpp::Message msg) {
    try {
        CommandHandler *handler = module->isHandler();
        Bot *bot = handler->hasBot();
        dpp::Guild guild = handler->isFromGuild();
        auto role_name = *msg.mention_roles.get();
        std::string load_msg = "";
        if(!role_name.empty()) {
            for(auto &role : role_name) {
                std::cout << "\033[1;36mFound role with id \033[1;35m" << role << "\033[0m" << std::endl;
                auto response = bot->getRoles(dpp::get_snowflake(guild.at(0)["id"]));
                auto roles = handler->adminRoles();
                std::cout << response.dump(4) << std::endl;
                if(response == NULL) {
                    bot->sendMessage(*msg.channel_id, false, "This server does not have any roles.");
                    throw CommandException("Could not execute " + this->getName(), EXECUTE_ERROR, 0);
                }
                for(std::size_t i = 0; i < response["body"].size(); ++i) {
                    if(role == response["body"].at(i)["id"] && !std::count(roles.begin(), roles.end(), role)) {
                        handler->addAdminRole(role);
                        std::cout << "\033[1;36m" << role << "\033[1;35m added to the adminlist for guild " << guild.at(0)["id"] << ".\033[0m" << std::endl;
                        bot->sendMessage(*msg.channel_id, false, "Added the role for you.");
                        dpp::json config = bot->config;
                        for(std::size_t i = 0; i < config["guild_settings"].size(); ++i) {
                            if(config["guild_settings"].at(i)["id"] == guild.at(0)["id"]) {
                                bool found = false;
                                for(std::size_t j = 0; j < config["guild_settings"].at(i)["adminroles"].size(); ++j) {
                                    if(!config["guild_settings"].at(i)["adminroles"].at(j).get<std::string>().compare(std::to_string(role))) {
                                        found = true;
                                        break;
                                    }
                                }
                                if(!found)
                                    config["guild_settings"].at(i)["adminroles"].push_back(role);
                                break;
                            }
                        }
                        bot->updateConfigFile(config);
                        std::cout << "\033[1;32mExecuted " + this->getName() + "\033[0m" << std::endl;
                        return;
                    }
                }
                load_msg = "Unable to find this role or this role is already added.";
                bot->sendMessage(*msg.channel_id, false, load_msg);
                throw CommandException("Could not execute " + this->getName(), EXECUTE_ERROR, 0);
            }
        } else {
            load_msg = "You have not given a role to add.";
            bot->sendMessage(*msg.channel_id, false, load_msg);
            throw CommandException("Could not execute " + this->getName(), PARAM_ERROR, 0);
        }
    } catch(CommandException &e) {
        std::cerr << "\033[1;31m" << e.what() << " \033[1;35mwith error code \033[1;36m" << e.getErrorNumber() << " \033[0m" << std::endl;
        module->isHandler()->setLastException(&e);
    }
}

bool AddAdmin::hasPermsToRun(dpp::User user) {
    auto handler = module->isHandler();
    std::vector<dpp::snowflake> admin = handler->adminRoles();
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
