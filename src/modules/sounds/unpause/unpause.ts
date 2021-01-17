import { CommandContext } from "../../../commandContext";
import { Command } from "../../command";
import { conn } from "../join/join";

export class UnpauseCommand implements Command {
    commandNames = ['unpause', 'continue'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}unpause to unpause the current song.`;
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        if (conn != undefined) {
            await conn.dispatcher.resume();
        } else 
            await parsedUserCommand.originalMessage.channel.send(`Not connected to a voice channel.`);
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        return true;
    }
}