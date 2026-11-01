# Building for iOS

The iOS port is built on macOS and lives in `platforms/ios`.

## Prerequisites

- Xcode with the iOS SDK
- CMake 3.25 or newer and Ninja
- Rust installed via [rustup](https://rustup.rs), with the iOS target added:

```sh
rustup target add aarch64-apple-ios
```

## Building

Clone the repository with its submodules:

```sh
git clone --recurse-submodules https://github.com/flyngmt/ACGC-PC-Port.git
cd ACGC-PC-Port
```

Configure and build the app from the repository root:

```sh
cmake --preset ios-arm64
cmake --build --preset ios-arm64
```

You'll find it at `build/ios-arm64/bin/Nookery.app`.

The app isn't signed. To install it, package it as an IPA and sideload it with
[iloader](https://iloader.app/), as described in [INSTALLING_IOS.md](INSTALLING_IOS.md):

```sh
cd build/ios-arm64/bin
mkdir -p Payload
cp -R Nookery.app Payload/
zip -r Nookery.ipa Payload
```

## Game files

Saves, the texture pack and NES ROMs live in the app's Documents folder,
which shows up under **On My iPhone > Nookery** in the Files app.
