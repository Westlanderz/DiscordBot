#include "../../include/commands/help.hpp"
#include "../../include/module.hpp"
#include "../../include/commandhandler.hpp"
#include "../../include/bot.hpp"
#include "../../include/commandexception.hpp"

Help::Help(std::vector<std::string> names): Command(names) {}

std::string Help::getHelpMessage() {
    return "I think you know how to use this command";
}

void Help::execute(dpp::Message msg) {
    try {
        std::vector<Command *> commands = module->isHandler()->getCommands();
        std::vector<Command *> allowed_commands;
        dpp::User sender;
        for(auto &command : commands) {
            if(command->hasPermsToRun(*msg.author.get()))
                allowed_commands.push_back(command);
        }
        std::size_t find_args = msg.content->find(" ");
        std::size_t find_command = msg.content->find(" ", find_args + 1);
        std::string command_name = "";
        if(find_args != std::string::npos) {
            if(find_command != std::string::npos) {
                command_name = msg.content->substr(find_args + 1, find_command - find_args);
            } else {
                command_name = msg.content->substr(find_args + 1);
            }
            for(auto &command : allowed_commands) {
                if(command->isName(command_name)) {
                    dpp::MessageEmbed embed;
                    embed.setAuthor(module->isHandler()->hasBot()->self["username"], "");
                    embed.setTitle("Generated help message");
                    embed.addField(command->getName(), command->getHelpMessage(), true);
                    embed.setColor(0xFFCC00);
                    command->isModule()->isHandler()->hasBot()->sendMessage(*msg.channel_id, embed);
                    return;
                }
            }
            module->isHandler()->hasBot()->sendMessage(*msg.channel_id, "Could not find the command you were looking for.");
            throw CommandException("Was not able to find " + command_name + " while executing " + this->getName(), FIND_ERROR, 0);
        } else {
            std::string help_msg = "Here is a list of commands you can run: ";
            for(auto &command : allowed_commands) {
                help_msg.append(command->getName());
                if(!command->getName().compare(allowed_commands.at(allowed_commands.size() - 1)->getName())) {
                    help_msg.append(". ");
                } else {
                    help_msg.append(", ");
                }
            }
            help_msg.append("Try " + module->isHandler()->isPrefix() + names[0] + " to learn more about one of them. Version: 0.1.0-a.1 https://github.com/Westlanderz/DiscordBot");
            module->isHandler()->hasBot()->sendMessage(*msg.channel_id, true, help_msg);
        }
    } catch(CommandException &e) {
        std::cerr << "\033[1;31m" << e.what() << "\033[0m stopped searching with error code \033[1;36m" << e.getErrorNumber() << "\033[0m" << std::endl;
        module->isHandler()->setLastException(&e);
    }    
}
