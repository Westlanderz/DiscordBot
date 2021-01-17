import { VoiceConnection } from "discord.js";
import { CommandContext } from "../../../commandContext";
import { Command } from "../../command";

export var conn: VoiceConnection;

export class JoinCommand implements Command {
    commandNames = ['join', 'connect'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}join to have the bot join in your current voice channel.`;
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        const sender = parsedUserCommand.originalMessage.member;
        const channel = sender.voice.channel;
        if (channel.joinable == true && channel.speakable == true){
            conn = await channel.join();
            await parsedUserCommand.originalMessage.channel.send(`Joined your channel.`);
        } else
            await parsedUserCommand.originalMessage.channel.send(`You need to be in a channel first.`);
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        return true;
    }
}