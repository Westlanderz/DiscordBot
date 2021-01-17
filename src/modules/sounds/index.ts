import { Module } from "../modules";
import { JoinCommand } from "./join/join";
import { DisconnectCommand } from "./leave/leave";
import { PauseCommand } from "./pause/pause";
import { PlayCommand } from "./play/play";
import { UnpauseCommand } from "./unpause/unpause";

export default class Sounds implements Module {
    moduleName: 'sounds';
    includedCommands: [
        JoinCommand,
        DisconnectCommand,
        PauseCommand,
        UnpauseCommand,
        PlayCommand
    ];
}