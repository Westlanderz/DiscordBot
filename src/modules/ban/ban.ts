import { BanOptions } from 'discord.js';
import { CommandContext } from '../../commandContext';
import { Command } from '../command';

export class BanCommand implements Command {
    commandNames = ['ban', 'remove'];

    
    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}ban [user] to ban a user from the server.`;
    }
    
    async run(parsedUserCommand: CommandContext): Promise<void> {
        if (parsedUserCommand.args.length === 0) {
            await parsedUserCommand.originalMessage.reply(`Please provide a user to ban`);
            await parsedUserCommand.originalMessage.delete();
            return;
        }
        const member = parsedUserCommand.originalMessage.mentions.members.first();
        if (member){
            const bannedMember = await member.ban();
            await parsedUserCommand.originalMessage.channel.send(`${bannedMember.user.username} has been banned from this server.`);
        }
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        if (parsedUserCommand.originalMessage.member.hasPermission(["BAN_MEMBERS"]) || parsedUserCommand.originalMessage.member.hasPermission(["ADMINISTRATOR"]))
            return true;
        return false;
    }
}

export class TempbanCommand implements Command {
    commandNames = ['tempban'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}tempban [user] [days] to ban a user from the server for a x amount of days.`;
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        if (parsedUserCommand.args.length === 0) {
            await parsedUserCommand.originalMessage.reply(`Please provide a user to ban`);
            await parsedUserCommand.originalMessage.delete();
            return;
        }

        if (parsedUserCommand.args[1] == undefined) {
            await parsedUserCommand.originalMessage.reply(`You must specify the amount of days for the temp ban, otherwise use !ban`);
            await parsedUserCommand.originalMessage.delete();
            return;
        }

        const member = parsedUserCommand.originalMessage.mentions.members.first();
        const days = parsedUserCommand.args[1];

        if (member && days) {
            const bannedMember = await member.ban({days: +days});
            await parsedUserCommand.originalMessage.channel.send(`${bannedMember.user.username} has been banned from this server for ${days} days.`);
        }
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        if (parsedUserCommand.originalMessage.member.hasPermission(["BAN_MEMBERS"]) || parsedUserCommand.originalMessage.member.hasPermission(["ADMINISTRATOR"]))
            return true;
        return false;
    }
}