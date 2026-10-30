# Xbox 360 target (work in progress)

This folder holds the Xbox 360 port layer for this fork of the Animal Crossing PC port.
The plan is to reuse the PC port's working game loop and platform layer (`pc/`) and
replace only the parts that depend on SDL2 and OpenGL with libxenon equivalents.

**Status:** scaffolding only. Nothing here builds the game yet. Four test variants of
`default.frag`, compiled without the XDK, have drawn correctly on a console through libxenon
(`tests/shader_smoke/`).

## Layout

| Path | Contents |
|---|---|
| `toolchain/` | Pinned devkitxenon/libxenon build (GCC 9.2.0, binutils 2.32, newlib 3.1.0, libxenon `c32c813`), `xenon_env.sh` |
| `patches/libxenon-input.patch` | libxenon USB controller attach/detach extension used by `src/pad_usb.c` |
| `src/` | Console-side code carried over from the earlier Codex prototype (see below) |
| `tools/package_xell.py` | Converts a linked ELF into a XeLL-loadable `xenon.elf` |
| `tools/shaders/` | `default.frag` variants through glslang, spirv-opt and `xsc`, plus simulator checks |
| `tests/shader_smoke/` | Console test that draws four compiled variants |
| `reference/codex/` | Earlier prototype material kept for reference, not built |

## Carried over from the Codex prototype

These were written and console-tested (where noted in `reference/codex/CONSOLE_CHECKPOINTS.md`)
in the earlier from-scratch attempt:

- `native_backend.c/.h` - Xenon timebase ticks scaled to GameCube timer units, UART logging,
  USB input init/poll, rumble, and hardware-thread worker start (for e.g. an audio thread).
- `time_scale.h` - 49.875 MHz Xenon timebase to 40.5 MHz GC timer conversion.
- `native_io.c` - libc file reads and aligned allocation.
- `pad_state.c/.h`, `pad_usb.c` - USB controller to GameCube PAD mapping (needs the libxenon patch).
- `batch_pacing.c/.h` - frame pacing on blank edges; smooth motion was confirmed on console.
- `compiler_compat.h`, `math_compat.h` - Metrowerks intrinsics and libm declarations for xenon-gcc.

## Reference only (`reference/codex/`)

- `codex-src-changes.patch` - Codex's `TARGET_XBOX360` edits to 119 game files. Most overlap
  fixes the PC port already makes under `TARGET_PC`; take individual hunks only when
  xenon-gcc still fails on a file.
- `gx_texture_xenos.c`, `xenos_clear_probe.c` - working Xe_* texture upload, clear/resolve/sync.
- `fat32_read.c`, `disc.c` - read-only USB FAT32 and GameCube disc/FST readers.
- Audit, continuation, console checkpoint and diagnostic reports.

## Next steps

1. Compile `default.vert` with `xsc`, measure the game's real variant set from `shader_cache.bin`,
   and decide what a variant missing from the precompiled set does. The ubershader itself does
   not compile; see `tools/shaders/README.md`.
2. Split `TARGET_PC` into a platform flag and a little-endian flag so byte swaps are off on Xbox.
3. Add an Xbox build (xenon-gcc, `-m32`) that compiles the game sources plus `pc/` minus SDL/GL files.
4. Port `pc/src/pc_gx.c` draw/state calls to `Xe_*`, then `pc_vi`, `pc_pad`, `pc_audio`.
5. Boot to the Nintendo logo through the original startup path.

## Toolchain

```sh
source xbox/toolchain/xenon_env.sh   # set DEVKITXENON first to reuse an existing install
xenon-gcc --version
```

See `toolchain/TOOLCHAIN.md` for rebuilding from the locked sources.
