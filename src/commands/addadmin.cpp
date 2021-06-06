#include "../../include/commands/addadmin.hpp"
#include "../../include/module.hpp"
#include "../../include/commandhandler.hpp"
#include "../../include/bot.hpp"
#include "../../include/commandexception.hpp"

#include <algorithm>

AddAdmin::AddAdmin(std::vector<std::string> names): Command(names) {}

std::string AddAdmin::getHelpMessage() {
    return "Use " + module->isHandler()->isPrefix() + names[0] + " <role> to add that role to the list of Admin roles.";
}

void AddAdmin::execute(dpp::Message msg) {
    try {
        dpp::Guild guild = module->isHandler()->isFromGuild();
        auto bot = module->isHandler()->hasBot()->hasDpp();
        std::size_t find_args = msg.content->find(" ");
        std::size_t find_role = msg.content->find(" ", find_args + 1);
        std::string role_name = "";
        std::string load_msg = "";
        if(find_args != std::string::npos) {
            if(find_role != std::string::npos) {
                role_name = msg.content->substr(find_args + 2, find_role - find_args);
            } else {
                role_name = msg.content->substr(find_args + 2);
            }
            module->isHandler()->hasBot()->hasDpp()->getGuildRoles()
                ->guild_id(dpp::get_snowflake(guild["id"]))
                ->onRead([this, role_name, msg](bool error, dpp::json response) {
                    auto roles = module->isHandler()->adminRoles();
                    auto role = dpp::get_snowflake(role_name);
                    for(std::size_t i = 0; i < response["body"].size(); ++i) {
                        if(role_name == response["body"].at(i)["id"] && !std::count(roles.begin(), roles.end(), role)) {
                            module->isHandler()->addAdminRole(role);
                            module->isHandler()->hasBot()->sendMessage(*msg.channel_id, false, "Added the role for you.");
                            std::cout << "\033[1;32mExecuted " + this->getName() + "\033[0m" << std::endl;
                            return;
                        }
                    }
                })
                ->run();
            load_msg = "Unable to find this role or this role is already added.";
            module->isHandler()->hasBot()->sendMessage(*msg.channel_id, false, load_msg);
            throw CommandException("Could not execute " + this->getName(), EXECUTE_ERROR, 0);
        } else {
            load_msg = "You have not given a role to add.";
            module->isHandler()->hasBot()->sendMessage(*msg.channel_id, false, load_msg);
            throw CommandException("Could not execute " + this->getName(), PARAM_ERROR, 0);
        }
    } catch(CommandException &e) {
        std::cerr << "\033[1;31m" << e.what() << " \033[1;35mwith error code \033[1;36m" << e.getErrorNumber() << " \033[0m" << std::endl;
        module->isHandler()->setLastException(&e);
    }
}

bool AddAdmin::hasPermsToRun(dpp::User user) {
    std::vector<dpp::snowflake> admin = module->isHandler()->adminRoles();
    std::vector<Module *> modules = module->isHandler()->getModules();
    dpp::Guild guild = module->isHandler()->isFromGuild();
    bool isAdmin = false;
    std::string authorid = user["id"].get<std::string>();
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