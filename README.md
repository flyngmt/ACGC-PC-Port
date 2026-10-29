# Animal Crossing PC Port

A native PC port of Animal Crossing (GameCube), based on the
[ac-decomp](https://github.com/ACreTeam/ac-decomp) decompilation.

This repository contains no game assets. A legally obtained GAFE01 Rev 0 (USA)
disc image is required; RVZ, ISO, and GCM images are accepted.

## Building and running

Install CMake 3.25 or newer, Ninja, and a C/C++20 toolchain.
Clone the repository with its submodules, then configure and build one of the included presets:

```sh
git clone --recurse-submodules https://github.com/flyngmt/ACGC-PC-Port.git
cd ACGC-PC-Port
cmake --preset relwithdebinfo
cmake --build --preset relwithdebinfo
./build/aurora/relwithdebinfo/bin/AnimalCrossing --disc /path/to/game.rvz
```

Use the `debug` preset for unoptimized builds with debug info.

### Android

With the Android SDK and NDK installed, build the arm64 native library and APK with:

```sh
export ANDROID_HOME="$HOME/Android/Sdk"
export ANDROID_NDK_VERSION="29.0.14206865"
cmake --preset android-arm64
cmake --build --preset android-arm64
cd platforms/android
./gradlew :app:assembleDebug
```

See [platforms/android/README.md](platforms/android/README.md) for prerequisites,
APK output paths, and launch-intent arguments.

## Controls

### Keyboard (defaults)

| Key | Action |
|-----|--------|
| WASD | Move (left stick) |
| Arrow Keys | Camera (C-stick) |
| Space | A button |
| Left Shift | B button |
| Enter | Start |
| X | X button |
| Y | Y button |
| Q / E | L / R triggers |
| Z | Z trigger |
| I / J / K / L | D-pad (up/left/down/right) |

### Gamepad

SDL3 game controllers are supported through Aurora, including hotplug and
persisted mappings.

Press F1 on a keyboard, Back/Select on a controller, or R + Start to open
the port menu. F3 toggles debug diagnostics.

## Command Line Options

| Flag | Description |
|------|-------------|
| `--disc PATH` | Open an RVZ, ISO, or GCM image; defaults to `game.rvz` |
| `--window-size WxH` | Set the initial window size |
| `--widescreen` | Start at 1280x720 instead of 4:3 |
| `--profile[=N]` | Show performance diagnostics |
| `--model-viewer[=index]` | Launch the model viewer at an optional structure index |
| `--framelimit N` | Set a software frame limit; 0 is uncapped |
| `--no-framelimit` | Run uncapped |
| `--time H[:M[:S]]` | Override the in-game clock |
| `--date M/D[/Y]` | Override the in-game date |
| `--rain[=intensity]` | Force `light`, `normal`, or `heavy` rain (default `heavy`) |
| `--verbose`, `-v` | Enable additional game diagnostics and debug logging |
| `--log-level LEVEL`, `-L` | Select `trace`, `debug`, `info`, `warning`, `error`, or `fatal` |
| `--log-dir PATH` | Override the rotating log-file directory |
| `--user-dir PATH` | Override the directory used for configuration, mappings, and saves |
| `--help`, `-h` | Show the generated option list |

Options whose value is optional (`--profile`, `--model-viewer`, `--rain`) must attach
it with `=`: `--rain=light`, not `--rain light`.

Run `AnimalCrossing --help` for the full option list.

## Data Folder

The data folder holds saves, `config.json`, `input.json`, `texture_pack/`,
and `nes_roms/`. Its default location is:

| Platform | Default data folder |
|---|---|
| Windows | The executable's folder (matching the pre-Aurora port); falls back to `%APPDATA%\Animal Crossing\` when that folder is not writable |
| macOS | `~/Library/Application Support/Animal Crossing/` |
| Linux | `~/.local/share/Animal Crossing/` |
| Android | The app's internal files directory, exposed through its system documents provider |

Use Settings > Data to move game data to a custom folder.

## Save Data

The home town lives at `save/card_a/DobutsunomoriP_MURA.gci` in the data
folder. Visited towns use `save/card_b/`.

## Credits

This project would not be possible without the work of the [ACreTeam](https://github.com/ACreTeam) decompilation team.
Their complete C decompilation of Animal Crossing is the foundation this port is built on.

Special thanks to the [Aurora](https://github.com/encounter/aurora) developers,
[Dusklight](https://github.com/TwilitRealm/dusklight) for inspiration, and all
[contributors](https://github.com/TwilitRealm/dusklight/graphs/contributors).

## FAQ

See [FAQ](FAQ.md) for more info.

<br/>
<div align="center">
    <a href="https://github.com/encounter/aurora">
        <img src="assets/aurora-powered.png" alt="Powered by Aurora" width="800">
    </a>
</div>
