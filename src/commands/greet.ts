import { CommandContext } from '../commandContext';
import { Command } from './command';

export class GreetCommand implements Command {
    commandNames = ['greet', 'hello'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}greet [user] to greet a user to the server.`;
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        await parsedUserCommand.originalMessage.channel.send(`Welcome to this Server, ${parsedUserCommand.args[0]}`);
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        return true;
    }
}