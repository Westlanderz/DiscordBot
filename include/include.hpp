//
// Created by Aidan on 10/2/2020.
//

#pragma once

#ifndef ECHO_EXTERN

#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

#include <boost/asio.hpp>

// Put more non-plugin `include`s here

#endif

#include "discordpp/bot.hh"
#include "discordpp/log.hh"
#include "discordpp/plugin-overload.hh"
#include "discordpp/plugin-ratelimit.hh"
#include "discordpp/plugin-responder.hh"
#include "discordpp/rest-beast.hh"
#include "discordpp/websocket-simpleweb.hh"
#include "discordpp/MessageEmbed.hh"
#include "discordpp/plugin-endpoints.hh"
#include "discordpp/plugin-constructs.hh"
#include "discordpp/plugin-interactionhandler.hh"

#ifndef ECHO_EXTERN

extern template class discordpp::PluginInteractionHandler<discordpp::PluginConstructs<discordpp::PluginEndpoints<discordpp::PluginResponder<discordpp::PluginOverload<discordpp::PluginRateLimit<discordpp::WebsocketSimpleWeb<discordpp::RestBeast<discordpp::Bot>>>>>>>>;
using DppBot = discordpp::PluginInteractionHandler<discordpp::PluginConstructs<discordpp::PluginEndpoints<discordpp::PluginResponder<discordpp::PluginOverload<discordpp::PluginRateLimit<discordpp::WebsocketSimpleWeb<discordpp::RestBeast<discordpp::Bot>>>>>>>>;

namespace asio = boost::asio;
using json = nlohmann::json;
namespace dpp = discordpp;

#undef DPPBOTDEF

#endif
