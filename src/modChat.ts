import { Message } from 'discord.js';

export interface ModChat {
    checkAllCaps(message: Message): boolean;
    checkBannedWords(message: Message, bannedWords: string[]): boolean;
    
}

export const modChat: ModChat = {
    checkAllCaps(message: Message): boolean {
        if (message.content == message.content.toUpperCase())
            return true;
        return false;
    },

    checkBannedWords(message: Message, bannedWords: string[]): boolean {
        let output = false;
        const splitMessage = message.content
            .trim()
            .split(/ +/g);
        bannedWords.forEach(word => {
            splitMessage.forEach(words => {
                console.log(word + ' ' + words);
                
                if (word == words)
                    output = true;
            })
        });
        return output;
    }
}