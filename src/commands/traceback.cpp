#include "../../include/commands/traceback.hpp"
#include "../../include/module.hpp"
#include "../../include/commandhandler.hpp"
#include "../../include/bot.hpp"
#include "../../include/commandexception.hpp"

#include<algorithm>

Traceback::Traceback(std::vector<std::string> names): Command(names) {}

std::string Traceback::getHelpMessage() {
    return "Use " + module->isHandler()->isPrefix() + names[0] + " [public] to get the last command exception. Public is false by default and will send it into your DMs";
}

void Traceback::execute(dpp::Message msg) {
    auto author = *msg.author.get();
    std::size_t find_args = msg.content->find(" ");
    std::size_t find_command = msg.content->find(" ", find_args + 1);
    std::string command_name = "";
    dpp::User owner;
    dpp::Guild guild = module->isHandler()->isFromGuild();
    if(find_args != std::string::npos) {
        if(find_command != std::string::npos) {
            command_name = msg.content->substr(find_args + 1, find_command - find_args);
        } else {
            command_name = msg.content->substr(find_args + 1);
        }
        std::transform(command_name.begin(), command_name.end(), command_name.begin(), ::tolower);
        if(!command_name.compare("true")) {
            module->isHandler()->hasBot()->sendMessage(*msg.channel_id, false, "errmsg");
        } else {
            for(std::size_t i = 0; i < guild.at(0)["members"].size(); i++) {
                if(guild.at(0)["members"].at(i)["user"]["id"] == author["id"]) {
                    owner = author;
                    module->isHandler()->hasBot()->sendMessage(owner, "errmsg");
                }
            }
        }
    } else {
        for(std::size_t i = 0; i < guild.at(0)["members"].size(); i++) {
            if(guild.at(0)["members"].at(i)["user"]["id"] == author["id"]){
                owner = author;
                module->isHandler()->hasBot()->sendMessage(owner, "TESTING");
            }
        }
    }
}
    

bool Traceback::hasPermsToRun(dpp::User user) {
    try {
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
    } catch (CommandException &e) {
        std::cerr << "\033[1;31m" << e.what() << " \033[1;36m" << e.getErrorNumber() + " " + e.getErrorOffset() << "\033[0m" << std::endl;
        module->isHandler()->setLastException(&e);
        return false;
    }
}
