# Shader smoke test

First console check of `default.frag` variants compiled with `xsc`, with no XDK output involved.
`smoke_shaders.h` is generated; the same pixel variants matched a Python TEV reference on `xsc`'s
simulator, but have not run on hardware.

## Run

Copy `build/xbox/shader-smoke/xenon.elf` to the root of a FAT32 USB stick, plug it in and boot XeLL.
A UART cable is optional but useful.

Rebuild from the repo root after `source xbox/toolchain/xenon_env.sh`:

```sh
O=build/xbox/shader-smoke; F="-DXENON -m32 -maltivec -fno-pic -mpowerpc64 -mhard-float"
xenon-gcc -g -O2 -Wall $F -I$DEVKITXENON/usr/include -c xbox/tests/shader_smoke/main.c -o $O/main.o
xenon-gcc $O/main.o $F -L$DEVKITXENON/xenon/lib/32 -Wl,--gc-sections -L$DEVKITXENON/usr/lib -lxenon -lm -n -T $DEVKITXENON/app.lds -o $O/shader_smoke.elf
python3 xbox/tools/package_xell.py --prefix "$DEVKITXENON" $O/shader_smoke.elf $O/xenon.elf
```

## What to expect

The background pulses between dark and brighter blue-green the whole time. Panels appear 5 seconds apart.

| Panel | Position | Should look like |
|---|---|---|
| 1 | Top left | A full square of orange and white checks, tinted by a pulsing green |
| 2 | Top right | A disc, not a square, of checks lit by moving coloured lights, turning red toward its right edge |
| 3 | Bottom left | Top and bottom visible with the middle band cut away, blue-to-yellow colours with some checker, slowly shifting light |
| 4 | Bottom right | A checker wobbling back and forth, mixed with blue-to-yellow, turning red toward its right edge |

## Reading failures

- **Background freezes:** the GPU hung. The newest panel is the suspect. Hold power to recover, as there is no GPU reset.
- **Black screen, XeLL never hands over:** the problem is before the shaders. Check the UART log.
- **Panel missing but background pulses:** the draw ran with wrong constants, export or vertex data.
- **Reds and blues swapped, or wrong alpha shapes:** probably the texture byte layout in `make_texture`, not the compiler.
- **Disc or band shapes wrong but colours right:** suspect the alpha `kill` path.

The UART log is unbuffered, so its last `stage N` line names the panel in use when a hang happened.
