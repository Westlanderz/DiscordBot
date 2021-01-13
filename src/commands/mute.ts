import { CommandContext } from '../commandContext';
import { Command } from './command';

export class MuteCommand implements Command {
    commandNames = ['mute'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}mute [user] to mute a certain user.`
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        const member = parsedUserCommand.originalMessage.mentions.members.first();
        if (member && member.voice.mute == false){
            const mutedMember = await member.voice.setMute(true);
            console.log(mutedMember.user.username);
            await parsedUserCommand.originalMessage.channel.send(`${mutedMember.user.username} has been muted.`);
        }
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        if (parsedUserCommand.originalMessage.member.hasPermission(["MUTE_MEMBERS"]) || parsedUserCommand.originalMessage.member.hasPermission(["ADMINISTRATOR"]))
            return true;
        return false;
    }
}

export class UnmuteCommand implements Command {
    commandNames = ['unmute'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}unmute [user] to unmute a certain user.`
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        const member = parsedUserCommand.originalMessage.mentions.members.first();
        if (member && member.voice.mute){
            const mutedMember = await member.voice.setMute(false);
            console.log(mutedMember.user.username);
            await parsedUserCommand.originalMessage.channel.send(`${mutedMember.user.username} has been unmuted.`);
        }
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        if (parsedUserCommand.originalMessage.member.hasPermission(["MUTE_MEMBERS"]) || parsedUserCommand.originalMessage.member.hasPermission(["ADMINISTRATOR"]))
            return true;
        return false;
    }
}