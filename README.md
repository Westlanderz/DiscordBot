# DiscordBot

![GitHub](https://img.shields.io/github/license/Westlanderz/discordbot)
![GitHub release (latest by date)](https://img.shields.io/github/v/release/westlanderz/discordbot)
![GitHub release (latest by date including pre-releases)](https://img.shields.io/github/v/release/westlanderz/discordbot?include_prereleases)
![GitHub issues](https://img.shields.io/github/issues/westlanderz/discordbot)
![Discord](https://img.shields.io/discord/692815534865121370)

## Table of Contents

1. [About The Project](#About)
    - [Status](#Status)
    - [Versioning](#Versioning)
2. [Getting Started](#Getting-started)
    - [Prerequisites](#Prerequisites)
    - [Dependencies](#Dependencies)
3. [Usage](#Usage)
    - [Compilation](#Compilation)
    - [Running](#Running)
4. [Release History](#Release-History)
5. [Roadmap](#Roadmap)
6. [Contributing](#Contributing)
7. [License](#License)
8. [Contact](#Contact)

## About

This is my own discord bot called YAGPDB2U, Yet Another General Purpose Discord Bot 2 Use
The goal is to make this a modular bot where everyone can make their own modules but it also comes with some default modules you can enable in your server.

### Status

This bot, when its run by me, has three versions: first we have a stable version, second we have a beta version with new not extensively tested features and last we have a dev build, this is basically an alpha build that has not been tested yet and changes a lot. Below this you can check the current build statusses of all these builds.

| Version        | Build status        |
| ------------- |:-------------:|
| **Master**     | [![Status Stable](http://vps.noahknegt.com:8050/api/projects/status/w9j9hdgpy5ubkv4s/branch/master?svg=true)](http://vps.noahknegt.com:8050/project/AppVeyor/discordbot/branch/master) |
| **Beta**     | [![Status Beta](http://vps.noahknegt.com:8050/api/projects/status/w9j9hdgpy5ubkv4s/branch/beta-releases?svg=true)](http://vps.noahknegt.com:8050/project/AppVeyor/discordbot/branch/beta-releases)      |
| **Dev** | [![Status Dev](http://vps.noahknegt.com:8050/api/projects/status/w9j9hdgpy5ubkv4s/branch/development?svg=true)](http://vps.noahknegt.com:8050/project/AppVeyor/discordbot/branch/development)     |

### Versioning

This bot is versioned as ` major.minor.patch `. Next to that it is possible it has a suffix in the next formatting:

| Stage  | Version       |
| ------ |:-------------:|
| **Alpha** | 1.1.0-a.1 |
| **Beta** | 1.1.0-b.4 |
| **Release candidate** | 1.1.0-rc.2 |
| **Release** | 1.2.0 |
| **Post-release fixes** | 1.2.4-a.1 |

## Getting started

### Prerequisites

To start using this project for your own you can either download a prebuild version from the github [releases](https://github.com/Westlanderz/Discordbot/releases) or [compile](#Compilation) it from source. To be able to run the program you need to have installed all the [dependencies](#Dependencies). It is tested on Linux so its able to run on that, but its not sure if it runs on Windows, so it is easier if you have a server or pc that runs Linux or run it in a VM.

### Dependencies

This bot is dependent on having [boost](https://www.boost.org/), [openssl](https://www.openssl.org/) and [json](https://github.com/nlohmann/json) installed. Futhermore this discordbot is build apon the [discordpp](https://github.com/DiscordPP/discordpp) library, this already included in the download of this repo. If you like to build your own bot look at their library or extend this implementation on theirs.

## Usage

As stated in the [prerequisites](#Prerequisites) section you can use this bot by compling it from source or download it. Under this section we listed the steps needed to compile it from source.

### Compilation

To compile this project, run the following commands in order:

```bash
git clone https://github.com/Westlanderz/Discordbot
cd Discordbot
mkdir bin ; cd bin
meson ..
ninja
```

### Running

Once you have downloaded or compiled the bot, complete the following steps to run the bot:

1. ` cd .. ` to move up one folder.
2. Get your discordbot secret from [here](https://discord.com/developers/applications).
3. ` echo Bot <secret> > token.dat ` (this only needs to be done once)
4. ` ./bin/discordbot `

## Release History

- v0.0.1 Node.js release

## Roadmap

Nothing on the ROADMAP at this given moment, if you would like a feature to be added either fill in a feature request [here](https://github.com/Westlanderz/discordbot/issues/new/choose) or follow the steps [in the section below](#Contributing).

## Contributing

Contributions are what make the open source community such an amazing place to be learn, inspire, and create. Any contributions you make are **greatly appreciated**.

1. Fork the Project
2. Create your Feature Branch (` git checkout -b feature/AmazingFeature `)
3. Commit your Changes (` git commit -m 'Add some AmazingFeature' `)
4. Push to the Branch (` git push origin feature/AmazingFeature `)
5. Open a Pull Request

## License

Distributed under the GPL-3.0 License. See `LICENSE` for more information.

## Contact

Noah Knegt - [@SenpaiR6](https://twitter.com/SenpaiR6) - admin@noahknegt.com

Project Link: [https://github.com/Westlanderz/Twitchbot](https://github.com/Westlanderz/Twitchbot)
