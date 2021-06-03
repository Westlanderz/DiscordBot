#include "../../include/commands/traceback.hpp"
#include "../../include/module.hpp"
#include "../../include/commandhandler.hpp"
#include "../../include/bot.hpp"
#include "../../include/commandexception.hpp"

Traceback::Traceback(std::vector<std::string> names): Command(names) {}

std::string Traceback::getHelpMessage() {
    return "Use " + module->isHandler()->isPrefix() + names[0] + " [public] to get the last command exception. Public is false by default and will send it into your DMs";
}

void Traceback::execute(dpp::Message msg) {
    auto author = *msg.author.get();
    dpp::User owner = json({});
    std::size_t find_args = msg.content->find(" ");
    std::size_t find_command = msg.content->find(" ", find_args + 1);
    std::string command_name = "";
    if(find_args != std::string::npos) {
        if(find_command != std::string::npos) {
            command_name = msg.content->substr(find_args + 1, find_command - find_args);
        } else {
            command_name = msg.content->substr(find_args + 1);
        }
    } else {
        module->isHandler()->hasBot()->sendMessage(*msg.channel_id.get(), "This is the tracback command. Implemantation comes later.");
    }
}
    

bool Traceback::hasPermsToRun(dpp::User user) {
    try {
        std::string owner = "SenpaiR6";
        std::vector<Module *> modules = module->isHandler()->getModules();
        dpp::Guild guild = module->isHandler()->isFromGuild();
        bool isOwner = false;
        std::string authorid = user["id"].get<std::string>();
        for(std::size_t i = 0; i < guild.at(0)["members"].size(); ++i) {
            if(guild.at(0)["members"].at(i)["user"]["id"] == authorid){
                if(guild.at(0)["members"].at(i)["user"]["username"].get<std::string>() == owner)
                    isOwner = true;
            }
        }
        if(!isOwner)
            throw(CommandException("Could not find the owner in this server " + module->isHandler()->isFromGuild().at(0)["name"].get<std::string>(), PERMISSION_ERROR, 0));
        else
            return isOwner;
    } catch (CommandException &e) {
        std::cerr << "\033[1;31m" << e.what() << " \033[1;36m" << e.getErrorNumber() + " " + e.getErrorOffset() << "\033[0m" << std::endl;
    }
}
