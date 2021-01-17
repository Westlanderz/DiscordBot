import { CommandContext } from "../../../commandContext";
import { Command } from "../../command";
import { conn } from "../join/join";
import * as ytdl from "ytdl-core";

// TODO: Fix the sound player
export class PlayCommand implements Command {
    commandNames = ['play', 'audio', 'listen'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}play [yt_link] to have the bot play songs your current voice channel.`;
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        conn.play(ytdl.default(parsedUserCommand.args[0], { filter: 'audioonly' }));
        await parsedUserCommand.originalMessage.channel.send(`Currently playing: ${parsedUserCommand.args[0]}`);
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        return true;
    }
}