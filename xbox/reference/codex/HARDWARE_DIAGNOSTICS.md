# User-operated hardware diagnostics — 2026-10-13

## Subsequent hardware results and real geometry diagnostic

The user confirmed a visible white GPU clear after adding the SDK example's
required `edram_init`. Earlier CPU controls matched/restored all six samples,
while the GPU clear changed none. The user then ran the original SDK cube
example and supplied a photograph of rotating textured geometry. Its nested
cube image is expected: the example binds the framebuffer as its texture.
These are user-operated hardware observations, not game or XEX execution.

The new `--diagnostic geometry` builder creates a separate harness from the
same SDK example. It retains the existing real shader binaries and matrix
code, replaces cube data with `inv_original_waku_model` vertices 4..35 and
its serialized 16-triangle batch, and runs the project decoder on that batch
on the console. Original GC and native object bytes must match before build.
Evidence and bounds are recorded in `geometry-evidence.json`. Positions are
centered/scaled for display, with diagnostic normals, no culling and a solid
white diagnostic texture instead of framebuffer feedback. This does not
interpret AC material/GX/texture state or execute gameplay. No game-derived
fixture arrays are committed; they are generated from local extracted objects.

```sh
source xbox360/xenon_env.sh
python3 xbox360/startup_probe.py --prefix "$DEVKITXENON" --diagnostic geometry
```

Copy `build/xbox360/geometry-testing/xenon.elf` to the USB root. The expected
result is fixed planar inventory-frame geometry, not a spinning cube or a
complete inventory screen. Python generation verifies matching original and
native asset bytes locally; generated PowerPC C syntax passes with only the
SDK harness's now-unused frame counter warnings. Native link and display of
this new geometry test remain unverified until built/run by the user.

The user ran the packaged startup ELF on a real Xbox 360 through XeLL
Reloaded (photographed v0.993-git-377ff28). The photograph shows CRT/main,
video initialization and framebuffer text checkpoints and the holding screen.
The user subsequently reported the isolated audio diagnostic beeped. This
confirms basic generated PCM output, not JAudio or game audio integration.
Exact tested binary hashes have not been supplied; retain build artifact.json
files to identify future tests. No game or XEX execution is established.

The first AV ELF was rejected because its LOAD addresses were not adjusted
for XeLL. The subsequent combined AV test flashed black and rebooted without
audible output or visible logs. Its logs used UART and its main returned;
that result does not identify which stage failed. The standalone builder now
applies libxenon's objcopy address adjustment once to a newly linked original.

Controller hardware testing is deferred: the user has wireless controllers
and no wired Xbox 360 controller. The current USB test does not implement
the console's internal wireless receiver. An eventual XEX input backend is
separate work.

## GPU clear test

From the repository root in Ubuntu:

```sh
source xbox360/xenon_env.sh
python3 xbox360/startup_probe.py --prefix "$DEVKITXENON" --diagnostic graphics
```

Copy `build/xbox360/graphics-testing/xenon.elf` to the FAT32 USB root.
Do not apply another address adjustment. The program displays checkpoints,
waits five seconds, then repeatedly clears/resolves/submits/synchronizes the
framebuffer using existing real libxenon APIs. It cycles five SDK color words
every two seconds (black, three primaries, white). Actual channel order needs
hardware observation. Text disappears on the first clear. Power off to exit.

Report the last visible checkpoint if it freezes; otherwise report the actual
color sequence and whether multiple complete cycles occur. A successful cycle
confirms this limited GPU path, not shader, texture, geometry, GX/VI or gameplay
support. No shader bytecode or game assets are included.

Local PowerPC Clang syntax checks with strict warnings and Python syntax
checks pass. Native GCC linking is performed by the user's Ubuntu build;
graphics execution remains unverified until the user reports the result.
