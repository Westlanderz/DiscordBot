import { CommandContext } from '../commandContext';

import { Command } from './command';

export class PingCommand implements Command {
    commandNames = ['ping'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}ping for a pong.`;
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        await parsedUserCommand.originalMessage.reply('pong!');
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean{
        return true;
    }
}