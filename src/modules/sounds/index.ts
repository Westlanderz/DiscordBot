import { Module } from "../modules";
import { JoinCommand } from "./join/join";
import { DisconnectCommand } from "./leave/leave";
import { PauseCommand } from "./pause/pause";
import { PlayCommand } from "./play/play";
import { UnpauseCommand } from "./unpause/unpause";

export default class Sounds implements Module {
    public readonly moduleName: string;
    public readonly includedCommands: any[];

    constructor() {
        this.moduleName = 'sounds';
        this.includedCommands = [
            JoinCommand,
            DisconnectCommand,
            PauseCommand,
            UnpauseCommand,
            PlayCommand
        ]
    }
}