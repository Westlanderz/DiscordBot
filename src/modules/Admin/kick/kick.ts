import Admin from '..';
import { CommandContext } from '../../../commandContext';
import { Command } from '../../command';

export class KickCommand implements Command {
    commandNames = ['kick', 'timeout'];

    
    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}kick [user] to kick a user from the server.`;
    }
    
    async run(parsedUserCommand: CommandContext): Promise<void> {
        const member = parsedUserCommand.originalMessage.mentions.members.first();
        if (member){
            const kickedMember = await member.kick();
            console.log(kickedMember.user.username);
            await parsedUserCommand.originalMessage.channel.send(`${kickedMember.user.username} has been kicked.`);
        }
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        if (parsedUserCommand.originalMessage.member.hasPermission(["KICK_MEMBERS"]) || parsedUserCommand.originalMessage.member.hasPermission(["ADMINISTRATOR"]))
            return true;
        return false;
    }
}





