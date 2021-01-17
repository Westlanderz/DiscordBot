import { CommandContext } from '../../commandContext';
import { Command } from '../../modules/command';
import { client } from "../../bot";

export class PingCommand implements Command {
    commandNames = ['ping'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}ping for a pong.`;
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        await parsedUserCommand.originalMessage.channel.send('pong! The current ping to the servers for this API is `' + Math.round(client.ws.ping) + 'ms`');
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean{
        return true;
    }
}