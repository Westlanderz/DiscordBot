import Discord from "discord.js";

function _is_submodule(parent, child): boolean {
    return parent == child || child.startsWith(parent + '.');
}

class BotBase {

    constructor(cli_flags, bot_dir: string = __dirname){
        this._config = Config.get_core_conf(force_registration = false)
        this._config.register_global(
            token=None,
            prefix=[],
            packages=[],
            owner=None,
            whitelist=[],
            blacklist=[],
            locale="en-US",
            regional_format=None,
            embeds=True,
            color=15158332,
            fuzzy=False,
            custom_info=None,
            help__page_char_limit=1000,
            help__max_pages_in_guild=2,
            help__delete_delay=0,
            help__use_menus=False,
            help__show_hidden=False,
            help__verify_checks=True,
            help__verify_exists=False,
            help__tagline="",
            help__use_tick=False,
            description="Red V3",
            invite_public=False,
            invite_perm=0,
            disabled_commands=[],
            disabled_command_msg="That command is disabled.",
            extra_owner_destinations=[],
            owner_opt_out_list=[],
            last_system_info__python_version=[3, 7],
            last_system_info__machine=None,
            last_system_info__system=None,
            schema_version=0,
            datarequests__allow_user_requests=True,
            datarequests__user_requests_are_strict=True,
        )
    }
}