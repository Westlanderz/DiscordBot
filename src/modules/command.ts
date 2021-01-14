import { CommandContext } from '../commandContext';

export interface Command {
    /**
     * List of aliases for the command.
     *
     * The first name in the list is the primary command name.
     */
    readonly commandNames: string[];
    getHelpMessage(commandPrefix: string): string;
    run(parsedUserCommand: CommandContext): Promise<void>;
    hasPermissionToRun(parsedUserCommand: CommandContext): boolean;
}