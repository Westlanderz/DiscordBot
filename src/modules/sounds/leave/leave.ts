import { CommandContext } from "../../../commandContext";
import { Command } from "../../command";

export class DisconnectCommand implements Command {
    commandNames = ['disconnect', 'leave', 'end'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}end to have the bot leave your current voice channel.`;
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        const sender = parsedUserCommand.originalMessage.member;
        const channel = sender.voice.channel;
            // TODO: Fix the destroy with check if it exsists
            //await conn.dispatcher.destroy();
        channel.leave();
        await parsedUserCommand.originalMessage.channel.send(`Left channel.`);
        
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        return true;
    }
}