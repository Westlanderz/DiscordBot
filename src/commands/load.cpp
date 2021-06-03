#include "../../include/commands/load.hpp"
#include "../../include/module.hpp"
#include "../../include/commandhandler.hpp"
#include "../../include/bot.hpp"

Load::Load(std::vector<std::string> names): Command(names) {}

std::string Load::getHelpMessage() {
    return "Use " + module->isHandler()->isPrefix() + names[0] + " <module> to load that module and make the commands available.";
}

void Load::execute(dpp::Message msg) {

}

bool Load::hasPermsToRun(dpp::User user) {
    // module->isHandler()->addAdminRole(798590668137562132);
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
    return isAdmin;
}
