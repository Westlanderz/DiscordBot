import { Module } from "../modules";
import { BanCommand, TempbanCommand } from "./ban/ban";
import { KickCommand } from "./kick/kick";
import { MuteCommand, UnmuteCommand } from "./mute/mute";
import { WarnCommand } from "./warn/warn";

export default class Admin implements Module {
    public readonly moduleName: string;
    public readonly includedCommands: any[];

    constructor() {
        this.moduleName = 'admin';
        this.includedCommands = [
            BanCommand,
            TempbanCommand,
            KickCommand,
            MuteCommand,
            UnmuteCommand,
            WarnCommand
        ];
    }
}