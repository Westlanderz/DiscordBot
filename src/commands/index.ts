import { GreetCommand } from "../modules/greet/greet";
import { Module } from "../modules/modules";
import { HelpCommand } from "./help/help";
import { PingCommand } from "./ping/ping";

export default class Default implements Module {
    public readonly moduleName: string;
    public readonly includedCommands: any[];

    constructor() {
        this.moduleName = 'default';
        this.includedCommands = [
            PingCommand,
            GreetCommand
        ];
    }
}