#include "../include/bot.hpp"

std::string getToken();

std::istream &safeGetline(std::istream &is, std::string &t);

void filter(std::string &target, const std::string &pattern);

int main() {
    dpp::log::filter = dpp::log::info;
    dpp::log::out = &std::cerr;

    std::cout << "Starting bot...\n\n";

    std::string token = getToken();
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

    uint16_t intents = dpp::intents::DIRECT_MESSAGE_REACTIONS
    | dpp::intents::DIRECT_MESSAGE_TYPING
    | dpp::intents::DIRECT_MESSAGES
    | dpp::intents::GUILD_BANS
    | dpp::intents::GUILD_EMOJIS
    | dpp::intents::GUILD_INTEGRATIONS
    | dpp::intents::GUILD_INVITES
    | dpp::intents::GUILD_MEMBERS
    | dpp::intents::GUILD_MESSAGE_REACTIONS 
    | dpp::intents::GUILD_MESSAGE_TYPING
    | dpp::intents::GUILD_MESSAGES
    | dpp::intents::GUILD_PRESENCES
    | dpp::intents::GUILD_VOICE_STATES
    | dpp::intents::GUILD_WEBHOOKS
    | dpp::intents::GUILDS;

    bot.setIntents(intents);
    bot.initServerJoiner();
    bot.initHandlers();
    bot.login(getToken());
    bot.run();

    return 0;
}

std::string getToken() {
    std::string token;
    char const *env = std::getenv("BOT_TOKEN");
    if (env != nullptr) {
        token = std::string(env);
    } else {
        std::ifstream tokenFile("../token.dat");
        if (!tokenFile) {
            return "";
        }
        safeGetline(tokenFile, token);
        tokenFile.close();
    }
    return token;
}

/*/
 * Source: https://stackoverflow.com/a/6089413/1526048
/*/
std::istream &safeGetline(std::istream &is, std::string &t) {
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf *sb = is.rdbuf();

    for (;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if (sb->sgetc() == '\n') {
                sb->sbumpc();
            }
            return is;
        case std::streambuf::traits_type::eof():
            // Also handle the case when the last line has no line endings
            if (t.empty()) {
                is.setstate(std::ios::eofbit);
            }
            return is;
        default:
            t += (char)c;
        }
    }
}
