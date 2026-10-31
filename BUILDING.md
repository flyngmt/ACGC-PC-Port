# Build Instructions

Install CMake 3.25 or newer, Python 3+, Ninja, and a C/C++20 toolchain.
Clone the repository with its submodules:

```sh
git clone --recurse-submodules https://github.com/flyngmt/ACGC-PC-Port.git
cd ACGC-PC-Port
```

## Windows

Install Visual Studio with the "Desktop development with C++" workload selected.
Either use the UI, or:
From an **x64 Native Tools Command Prompt for VS** (or after running
`vcvars64.bat`), configure and build the MSVC preset:

```bat
cmake --preset windows-msvc-relwithdebinfo
cmake --build --preset windows-msvc-relwithdebinfo
```

Use the `windows-msvc-debug` preset for unoptimized builds with debug info.


## Linux and macOS

Configure and build one of the included presets:

```sh
cmake --preset relwithdebinfo
cmake --build --preset relwithdebinfo
```

Use the `debug` preset for unoptimized builds with debug info.

## Android

See [BUILDING_ANDROID.md](BUILDING_ANDROID.md).
