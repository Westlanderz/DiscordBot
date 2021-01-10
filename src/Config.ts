/**
 * Discord bot config.
 *
 * Revisions to this file should not be committed to the repository.
 */
export type BotConfig = {
    token: string;
    prefix: string;
    botOwnerRoleName: string;
    enableReactions: boolean;
};

export const config: BotConfig = {
    token: '', // TODO: Put your token here!
    prefix: '!', // Command prefix. ex: !help
    botOwnerRoleName: 'bot-owner',
    enableReactions: true,
};