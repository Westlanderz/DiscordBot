import { CommandContext } from '../commandContext';
import { Command } from './command';

export class BanCommand implements Command {
    commandNames = ['ban', 'remove'];

    
    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}ban [user] to ban a user from the server.`;
    }
    
    async run(parsedUserCommand: CommandContext): Promise<void> {
        const member = parsedUserCommand.originalMessage.mentions.members.first();
        if (member){
            const bannedMember = await member.ban();
            console.log(bannedMember.user.username);
            await parsedUserCommand.originalMessage.channel.send(`${bannedMember.user.username} has been banned from this server.`);
        }
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        if (parsedUserCommand.originalMessage.member.hasPermission(["BAN_MEMBERS"]) || parsedUserCommand.originalMessage.member.hasPermission(["ADMINISTRATOR"]))
            return true;
        return false;
    }
}