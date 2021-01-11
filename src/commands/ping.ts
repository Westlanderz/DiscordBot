import { CommandContext } from '../commandContext';
import { Command } from './command';
import { client } from "../bot";

export class PingCommand implements Command {
    commandNames = ['ping'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}ping for a pong.`;
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        await parsedUserCommand.originalMessage.reply('pong! The current ping to the servers for this API is `' + Math.round(client.ws.ping) + 'ms`');
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean{
        return true;
    }
}