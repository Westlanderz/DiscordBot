#include "../include/bot.hpp"
#include "../include/discordpp/log.hh"
#include <fstream>

std::string getToken(dpp::json);

int main() {
    dpp::log::filter = dpp::log::info;
    dpp::log::out = &std::cerr;

    std::ifstream configfile("../config.json");
    dpp::json config = dpp::json::parse(configfile);
    configfile.close();

    std::cout << "Starting bot...\n\n";

    std::string token = getToken(config);
    if (token.empty()) {
        std::cerr << "CRITICAL: "
                  << "There is no valid way for Echo to obtain a token! Use "
                     "one of the following ways:"
                  << std::endl
                  << "(1) Fill the BOT_TOKEN environment variable with the "
                     "token (e.g. 'Bot 123456abcdef')."
                  << std::endl
                  << "(2) Copy the example `token.eg.dat` as `token.dat` and "
                     "write your own token to it.\n";
        exit(1);
    }

    Bot bot("DevBot", "!");

    bot.setIntents(std::stoull(config["intents"].get<std::string>()));
    bot.initServerJoiner();
    bot.initHandlers();
    bot.login(token);
    bot.run();

    return 0;
}

std::string getToken(dpp::json config) {
    std::string token;
    char const *env = std::getenv("BOT_TOKEN");
    if (env != nullptr) {
        token = std::string(env);
    } else {
        token = "Bot ";
        token.append(config["token"]);
    }
    return token;
}
