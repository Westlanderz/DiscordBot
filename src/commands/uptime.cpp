#include "../../include/commands/uptime.hpp"
#include "../../include/module.hpp"
#include "../../include/commandhandler.hpp"
#include "../../include/bot.hpp"
#include "../../include/commandexception.hpp"

using namespace bot;

Uptime::Uptime(std::vector<std::string> names): Command(names) {}

std::string Uptime::getHelpMessage() {
    return "Use " + module->isHandler()->isPrefix() + names[0] + " to see the current uptime of this bot.";
}

void Uptime::execute(dpp::Message msg) {
    auto uptime = (int64_t)module->isHandler()->hasBot()->uptime();
    std::string output = "The current uptime of this bot is: ";
    int64_t years, months, days, hours, minutes, seconds;
    int64_t temp_years, temp_months, temp_days, temp_hours;
    years = uptime / 31556952;
    temp_years = uptime % 31556952;
    months = temp_years / 2629800;
    temp_months = temp_years % 2629800;
    days = temp_months / 86400;
    temp_days = temp_months % 86400;
    hours = temp_days / 3600;
    temp_hours = temp_days % 3600;
    minutes = temp_hours / 60;
    seconds = temp_hours % 60;
    if(years != 0)
        output.append(std::to_string(years)).append(years > 1 ? " years, " : " year, ");
    if(months != 0 || years > 0)
        output.append(std::to_string(months)).append(months > 1 ? " months, " : " month, ");
    if(days != 0 || months > 0 || years > 0)
        output.append(std::to_string(days)).append(days > 1 ? " days, " : " day, ");
    if(hours != 0 || days > 0 || months > 0 || years > 0)
        output.append(std::to_string(hours)).append(hours > 1 ? " hours, " : " hour, ");
    if(minutes != 0 || hours > 0 || days > 0 || months > 0 || years > 0)
        output.append(std::to_string(minutes)).append(minutes > 1 ? " minutes, " : " minute, ");
    if(seconds != 0 || minutes > 0 || hours > 0 || days > 0 || months > 0 || years > 0)
        output.append(std::to_string(seconds)).append(seconds > 1 ? " seconds." : " second.");
    module->isHandler()->hasBot()->sendMessage(*msg.channel_id, false, output);
}
