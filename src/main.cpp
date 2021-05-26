#include "../include/include.hpp"

namespace asio = boost::asio;
using json = nlohmann::json;
namespace dpp = discordpp;

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

    std::shared_ptr<DppBot> bot = newBot();

    bot->debugUnhandled = false;

    bot->intents = dpp::intents::DIRECT_MESSAGE_REACTIONS
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
    // | dpp::intents::GUILD_PRESENCES //Buggy buggy
    | dpp::intents::GUILD_VOICE_STATES
    | dpp::intents::GUILD_WEBHOOKS
    | dpp::intents::GUILDS;

    /*/
     * Create handler for the READY payload, this may be handled by the bot in
    the future.
     * The `self` object contains all information about the 'bot' user.
    /*/
    json self;
    bot->handlers.insert(
        {"READY", [&self](json data) { self = data["user"]; }});

    bot->prefix = "~";

    bot->respond("help", "Mention me and I'll echo your message back!");
    
    bot->respond("about", [&bot](json msg) {
      std::ostringstream content;
      content
          << "Sure thing, "
          << (msg["member"]["nick"].is_null()
              ? msg["author"]["username"].get<std::string>()
              : msg["member"]["nick"].get<std::string>())
          << "!\n"
          << "I'm a simple bot meant to demonstrate the Discord++ library.\n"
          << "You can learn more about Discord++ at "
             "https://discord.gg/0usP6xmT4sQ4kIDh";
      bot->call("POST",
          "/channels/" + msg["channel_id"].get<std::string>() +
          "/messages",
          json({{"content", content.str()}}));
    });

    // Create handler for the MESSAGE_CREATE payload, this receives all messages
    // sent that the bot can see.
    bot->handlers.insert(
        {"MESSAGE_CREATE", [&bot, &self](json msg) {
             // Scan through mentions in the message for self
             bool mentioned = false;
             for (const json &mention : msg["mentions"]) {
                 mentioned = mentioned or mention["id"] == self["id"];
             }
             if (mentioned) {
                 // Identify and remove mentions of self from the message
                 std::string content = msg["content"].get<std::string>();
                 unsigned int oldlength, length = content.length();
                 do{
                     oldlength = length;
                     content = std::regex_replace(
                         content,
                         std::regex(R"(<@!?)" + self["id"].get<std::string>() +
                                    R"(> ?)"),
                         "");
                     length = content.length();
                 }while(oldlength > length);

                 // Get the target user's display name
                 std::string name =
                     (msg["member"]["nick"].is_null()
                          ? msg["author"]["username"].get<std::string>()
                          : msg["member"]["nick"].get<std::string>());

                 std::cout << "Echoing " << name << '\n';

                 // Echo the created message
                 bot->call("POST",
                           "/channels/" + msg["channel_id"].get<std::string>() +
                               "/messages",
                           json({{"content", content}}));

                 // Set status to Playing "with [author]"
                 bot->send(3,
                           {{"game", {{"name", "with " + name}, {"type", 0}}},
                            {"status", "online"},
                            {"afk", false},
                            {"since", "null"}});
             }
         }});

    std::shared_ptr<asio::io_context> aioc = std::make_shared<asio::io_context>();

    bot->initBot(6, token, aioc);

    bot->run();

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
