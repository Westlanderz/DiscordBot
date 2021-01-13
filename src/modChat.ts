import { Message } from 'discord.js';

export interface ModChat {
    checkAllCaps(message: Message): boolean;
    checkBannedWords(message: Message): boolean;
}