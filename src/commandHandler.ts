import { Message } from 'discord.js';
import { Command } from './modules/command';
import { HelpCommand } from './modules/help/help';
import { CommandContext } from './commandContext';
import { reactor } from './reactor';
import { ModChat } from './modules/autoMod/modChat';
import Admin from './modules/Admin';
import { Module } from './modules/modules';

//* Handler for bot commands issued by users. *//
export class CommandHandler {
    private commands: Command[];
    private modules: Module[];
    private readonly prefix: string;
    private commandClasses: any[];
    private moduleClasses: any[];
    

    constructor(prefix: string) {
        this.commandClasses = [
            // TODO: Add more commands here.
            // TODO: Only add default modules
            // TODO: clear messages command, XP commands/ Points, sound skip commands, queue command, R6 commands, Twitch commands, Role commands, 
        ];

        this.moduleClasses = [
            Admin
        ];

        this.commands = this.commandClasses.map((CommandClass) => new CommandClass());
        this.modules = this.moduleClasses.map((ModuleClass) => new ModuleClass());
        this.commands.push(new HelpCommand(this.commands));
        this.prefix = prefix;
    }

    //* Executes user commands contained in a message if appropriate. *//
    async handleMessage(message: Message): Promise<void> {
        if (message.author.bot || !this.isCommand(message)) {
            return;
        }

        // TODO: fix the auto mod stuff
        // let mod: ModChat;
        // if (mod.checkAllCaps(message) || mod.checkBannedWords(message)) {
        //     await message.delete();
        //     await message.channel.send(`@${message.author.username} you have been warned for: `)
        //     return;
        // }

        const commandContext = new CommandContext(message, this.prefix);

        const allowedCommands = this.commands.filter((command) =>
            command.hasPermissionToRun(commandContext),
        );

        const matchedCommand = this.commands.find((command) =>
            command.commandNames.includes(commandContext.parsedCommandName),
        );

        if (message.type == 'GUILD_MEMBER_JOIN') {
            await message.channel.send(`Welcome to this Server`);
            return;
        }

        if (commandContext.parsedCommandName === 'load' && message.member.hasPermission('ADMINISTRATOR')){
            const module = this.modules.find((module: Admin) =>{
                if (module.moduleName == commandContext.args[0])
                    return Admin;
            });
            this.loadModule(module);
        } else if (commandContext.parsedCommandName === 'load' && !message.member.hasPermission('ADMINISTRATOR')) {
            await message.reply(`You have no permission to run this command`);
            await message.delete();
            return;
        } else if (commandContext.parsedCommandName === 'unload' && message.member.hasPermission('ADMINISTRATOR')){
            const module = this.modules.find((command) =>
                command.moduleName.includes(commandContext.args[0]),
            );
            this.unloadModule(module);
        } else if (commandContext.parsedCommandName === 'unload' && !message.member.hasPermission('ADMINISTRATOR')) {
            await message.reply(`You have no permission to run this command`);
            await message.delete();
            return;
        } else if (!matchedCommand) {
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

    private loadModule(module) {
        module.includedCommands.forEach(commandClass => {
            this.commandClasses = [...this.commandClasses, commandClass];
            console.log(`Loaded ${commandClass}`);
        });
        this.commands = this.commandClasses.map((CommandClass) => new CommandClass());
    }

    private unloadModule(module) {
        module.includedCommands.forEach(commandClass => {
            const index = this.commandClasses.find(commandClass);
            this.commandClasses = this.commandClasses.splice(index, 1);
        })
    }

    /** 
     * Determines whether or not a message is a user command. 
     * @param message Takes a Message from discord
     */
    private isCommand(message: Message): boolean {
        return message.content.startsWith(this.prefix);
    }
}