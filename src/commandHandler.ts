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
    private loadedModules: any[];    

    constructor(prefix: string) {
        this.commandClasses = [
            // TODO: Add more commands here.
            // TODO: clear messages command, XP commands/ Points, sound skip commands, queue command, R6 commands, Twitch commands, Role commands, 
        ];

        this.moduleClasses = [
            // TODO: Only add default modules
            Admin,
        ];

        this.loadedModules = [
            
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
            if (commandContext.args.length === 0){
                const modulesUnloaded: any[] = [];
                for (let i = 0; i < this.modules.length; i++) {
                    for (let j = 0; j < this.loadedModules.length; j++) {
                        if (this.modules[i] != this.loadedModules[j])
                            modulesUnloaded.push(this.modules[i]);
                    }
                }
                const moduleNames = modulesUnloaded.map(
                    (module) => module.moduleName,
                );
                
                await commandContext.originalMessage.reply('You must provide a module to load, here is a list of modules you can load: `' + moduleNames.join(
                    ', ',
                ) + '`');
            } else {
                const module = this.modules.find((module) =>
                    module.moduleName.includes(commandContext.args[0]),
                );
                this.loadModule(module, message);
            }
        } else if (commandContext.parsedCommandName === 'load' && !message.member.hasPermission('ADMINISTRATOR')) {
            await message.reply(`You have no permission to run this command`);
            await message.delete();
            return;
        } else if (commandContext.parsedCommandName === 'unload' && message.member.hasPermission('ADMINISTRATOR')){
            if (commandContext.args.length === 0){
                const moduleNames = this.loadedModules.map(
                    (module) => module.moduleName,
                );
                await commandContext.originalMessage.reply('You must provide a module to unload, here is a list of modules you can load: `' + moduleNames.join(
                    ', ',
                ) + '`');
            } else {
                const module = this.modules.find((module) =>
                    module.moduleName.includes(commandContext.args[0]),
                );
                this.unloadModule(module, message);
            }
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

    private loadModule(module: any, message: Message): void {
        module.includedCommands.forEach(commandClass => {
            this.commandClasses = [...this.commandClasses, commandClass];
        });
        this.loadedModules.push(module);
        this.updateCommands();
        message.channel.send(`Loaded the module ${module.moduleName}`);
    }

    private unloadModule(module: any, message: Message): void {
        for (let i = 0; i < this.commandClasses.length; i++) {
            for (let j = 0; j < module.includedCommands.length; j++) {
                if (this.commandClasses[i] == module.includedCommands[j])
                    this.commandClasses.splice(i, 1);
            }
        }
        for (let i = 0; i < this.loadedModules.length; i++) {
            if (module == this.loadedModules[i])
                this.loadedModules.splice(i, 1);
        }
        this.updateCommands();
        message.channel.send(`Unloaded the module ${module.moduleName}`)
    }

    private updateCommands(): void {
        this.commands = this.commandClasses.map((CommandClass) => new CommandClass());
        this.commands.push(new HelpCommand(this.commands));
    }

    /** 
     * Determines whether or not a message is a user command. 
     * @param message Takes a Message from discord
     */
    private isCommand(message: Message): boolean {
        return message.content.startsWith(this.prefix);
    }
}