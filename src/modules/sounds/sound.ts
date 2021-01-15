import { CommandContext } from "../../commandContext";
import { Command } from "../command";
import * as ytdl from "ytdl-core";

var conn;

class Sounds {
    moduleName: 'sounds';
}
export class JoinCommand extends Sounds implements Command {
    commandNames = ['join'];

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

// TODO: Fix the sound player
export class PlayCommand extends Sounds implements Command {
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

export class PauseCommand extends Sounds implements Command {
    commandNames = ['pause', 'break'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}pause to pause the current song.`;
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        if (conn != null) {
            await conn.dispatcher.pause();
        } else 
            await parsedUserCommand.originalMessage.channel.send(`Not connected to a voice channel.`);
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        return true;
    }
}

export class UnpauseCommand extends Sounds implements Command {
    commandNames = ['unpause', 'continue'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}unpause to unpause the current song.`;
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        if (conn != null) {
            await conn.dispatcher.resume();
        } else 
            await parsedUserCommand.originalMessage.channel.send(`Not connected to a voice channel.`);
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        return true;
    }
}

export class EndCommand extends Sounds implements Command {
    commandNames = ['end', 'leave'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}end to have the bot leave your current voice channel.`;
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        const sender = parsedUserCommand.originalMessage.member;
        const channel = sender.voice.channel;
        if (conn != null) {
            // TODO: Fix the destroy with check if it exsists
            //await conn.dispatcher.destroy();
            await channel.leave();
            await parsedUserCommand.originalMessage.channel.send(`Left channel.`);
        } else
            await parsedUserCommand.originalMessage.channel.send(`Already not in a channel.`);

    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        return true;
    }
}