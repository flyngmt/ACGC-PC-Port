# Building for Android

The Android port lives in `platforms/android` and is packaged with the
Borealis Android shell.

## Prerequisites

- Android SDK installed (`ANDROID_HOME` or `ANDROID_SDK_ROOT`)
- Android NDK selected with `ANDROID_NDK_VERSION`
- JDK 17 or newer
- CMake 3.25 or newer and Ninja

## Building

Clone the repository with its submodules:

```sh
git clone --recurse-submodules https://github.com/flyngmt/ACGC-PC-Port.git
cd ACGC-PC-Port
```

Configure and build the native arm64 library from the repository root:

```sh
export ANDROID_HOME="$HOME/Android/Sdk"
export ANDROID_NDK_VERSION="29.0.14206865"
cmake --preset android-arm64
cmake --build --preset android-arm64
```

Then build the APK:

```sh
cd platforms/android
./gradlew :app:assembleDebug
```

You'll find it at `platforms/android/app/build/outputs/apk/debug/app-arm64-v8a-debug.apk`.

## Launch arguments

You can pass command line options through adb:

```sh
adb shell am start \
  -n com.flyngmt.nookery/dev.encounter.borealis.BorealisActivity \
  --es borealis_args "--verbose --log-level debug"
```

`borealis_args` takes the options as a single string. If you'd rather pass them
as a list, use `borealis_argv` with `--esa` instead.
