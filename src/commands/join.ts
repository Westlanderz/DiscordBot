import { CommandContext } from "../commandContext";
import { Command } from "./command";

export class JoinCommand implements Command {
    commandNames = ['join'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}join to have the bot join in your current voice channel.`
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        const sender = parsedUserCommand.originalMessage.member;
        const channel = sender.voice.channel;
        if (channel.joinable == true)
            channel.join();
        await parsedUserCommand.originalMessage.channel.send(`Joined your channel.`);

    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        return true;
    }
}