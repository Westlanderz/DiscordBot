import { Message } from 'discord.js';
import { Command } from './commands/command';
import { HelpCommand } from './commands/help';
import { CommandContext } from './commandContext';
import { reactor } from './reactor';
import { GreetCommand } from './commands/greet';
import { PingCommand } from './commands/ping';
import { WarnCommand } from './commands/warn';
import { KickCommand } from './commands/kick';
import { MuteCommand } from './commands/mute';
import { UnmuteCommand } from './commands/unmute';
import { JoinCommand } from './commands/join';

//* Handler for bot commands issued by users. *//
export class CommandHandler {
    private commands: Command[];

    private readonly prefix: string;

    constructor(prefix: string) {
        const commandClasses = [
            // TODO: Add more commands here.
            GreetCommand,
            PingCommand,
            WarnCommand,
            KickCommand,
            MuteCommand,
            UnmuteCommand,
            JoinCommand,
        ];

        this.commands = commandClasses.map((CommandClass) => new CommandClass());
        this.commands.push(new HelpCommand(this.commands));
        this.prefix = prefix;
    }

    //* Executes user commands contained in a message if appropriate. *//
    async handleMessage(message: Message): Promise<void> {
        if (message.author.bot || !this.isCommand(message)) {
            return;
        }

        const commandContext = new CommandContext(message, this.prefix);

        const allowedCommands = this.commands.filter((command) =>
            command.hasPermissionToRun(commandContext),
        );

        const matchedCommand = this.commands.find((command) =>
            command.commandNames.includes(commandContext.parsedCommandName),
        );

        if (message.type == 'GUILD_MEMBER_JOIN'){
            await this.commands.find((command) => command.commandNames.includes('GreetCommand')).run(commandContext);
        }

        if (!matchedCommand) {
            await message.reply("I don't recognize that command. Try !help.");
            await reactor.failure(message);
        } else if (!allowedCommands.includes(matchedCommand)) {
            await message.reply("You aren't allowed to use that command. Try !help.");
            await reactor.failure(message);
        } else {
            await matchedCommand
                .run(commandContext)
                .then(() => {
                    //reactor.success(message);
                    console.log(`* ${matchedCommand.commandNames[0]} executed succesfully`)
                })
                .catch((reason) => {
                    reactor.failure(message);
                    console.log(`Something went wrong with executing ${matchedCommand.commandNames[0]}, ${reason}`);
                });
        }
    }

    /** Determines whether or not a message is a user command. */
    private isCommand(message: Message): boolean {
        return message.content.startsWith(this.prefix);
    }
}