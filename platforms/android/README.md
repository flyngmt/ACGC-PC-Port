# Android Port

This directory contains ACPC's Android shell based on Borealis.

## Prerequisites

- Android SDK installed (`ANDROID_HOME` or `ANDROID_SDK_ROOT`)
- Android NDK selected with `ANDROID_NDK_VERSION`
- JDK 17 or newer
- CMake 3.25 or newer and Ninja

## Build

Configure and build the native arm64 library from the repository root:

```sh
export ANDROID_HOME="$HOME/Android/Sdk"
export ANDROID_NDK_VERSION="29.0.14206865"
cmake --preset android-arm64
cmake --build --preset android-arm64
```

Then package it with the Borealis Android shell:

```sh
cd platforms/android
./gradlew :app:assembleDebug
```

The APK is written to
`app/build/outputs/apk/debug/app-arm64-v8a-debug.apk`.

Aurora requires a hardware-backed graphics adapter. Launch an Android emulator
with `-gpu host` when GPU acceleration is not already enabled.

## Runtime Arguments

Borealis accepts command-line arguments through launch-intent extras:

```sh
adb shell am start \
  -n com.flyngmt.nookery/dev.encounter.borealis.BorealisActivity \
  --es borealis_args "--backend vulkan"
```

Supported extras are `borealis_args`, a shell-like argument string, and
`borealis_argv`, a string-array argument list.
