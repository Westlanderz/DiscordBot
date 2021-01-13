import { CommandContext } from '../commandContext';
import { Command } from './command';
import * as fs from "fs";

export class WarnCommand implements Command {
    commandNames = ['warn'];

    getHelpMessage(commandPrefix: string): string {
        return `Use ${commandPrefix}warn [user] <reason> to warn a user with or without a reason.`
    }

    async run(parsedUserCommand: CommandContext): Promise<void> {
        const args = parsedUserCommand.args;
        if (args.length === 0) {
            await parsedUserCommand.originalMessage.reply(`You have to specify a user to warn.`);
            return;
        }

        if (args[1] !== null && args[1] !== undefined) {
            let msg = `${args[0]} you have been warned for the following reason: \n`;
            for (let index = 1; index < args.length; ++index) {
                msg += args[index];
                msg += ' ';
            }
            await parsedUserCommand.originalMessage.channel.send(msg);
            return;
        }

        await parsedUserCommand.originalMessage.channel.send(`${args[0]} you have been warned.`);
    }

    hasPermissionToRun(parsedUserCommand: CommandContext): boolean {
        if (parsedUserCommand.originalMessage.member.hasPermission(["KICK_MEMBERS"]) || parsedUserCommand.originalMessage.member.hasPermission(["ADMINISTRATOR"]))
            return true;
        return false;
    }
}