#include "../../include/commands/traceback.hpp"
#include "../../include/module.hpp"
#include "../../include/commandhandler.hpp"
#include "../../include/bot.hpp"

Traceback::Traceback(std::vector<std::string> names): Command(names) {}

std::string Traceback::getHelpMessage() {
    return "Use " + module->isHandler()->isPrefix() + names[0] + " [public] to get the last command exception. Public is false by default and will send it into your DMs";
}

void Traceback::execute(dpp::Message msg) {
    module->isHandler()->hasBot()->sendMessage(*msg.channel_id, "This is the tracback command. Implemantation comes later.");
}
