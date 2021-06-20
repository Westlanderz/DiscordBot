#ifndef BOTINTERFACE_HPP
#define BOTINTERFACE_HPP

#include "include.hpp"

/**
 * @brief Creates a new shared pointer to a DppBot
 * 
 * @return std::shared_ptr<DppBot> 
 */
inline std::shared_ptr<DppBot> newBot(){
    return std::make_shared<DppBot>();
}

namespace bot {
    class BotInterface {
        private:
            std::shared_ptr<DppBot> bot;
        
        public:
            BotInterface() {
                this->bot = newBot();
            }
            virtual ~BotInterface() = default;
            std::shared_ptr<DppBot> isDppBot() { return bot; };
    };
}

#endif // BOTINTERFACE_HPP
