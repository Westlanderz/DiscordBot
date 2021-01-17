import { CommandContext } from "../../../commandContext";
import { Command } from "../../command";
import { conn } from "../join/join";

export class PauseCommand implements Command {
    commandNames = ['pause', 'break'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}pause to pause the current song.`;
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        if (conn != undefined) {
            await conn.dispatcher.pause();
        } else 
            await parsedUserCommand.originalMessage.channel.send(`Not connected to a voice channel.`);
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        return true;
    }
}