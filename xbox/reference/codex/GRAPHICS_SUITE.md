# Combined graphics diagnostic — 2026-10-13

The user photographed both batches with distinct textures in the preceding
multi-list composition. The new suite replaces that composition with a parent
list calling two separately bounded original list bodies. Calls and branches
share vertex/material state, with depth limited to eight and total decoded
commands to 4096. Unsupported opcodes remain explicit errors. Nested command
offsets in reports refer to the failing child span, not a global byte offset.

The native suite automatically cycles five labeled stages, ten seconds each:

1. Nested original lists, two independent textures.
2. SDK model-view rotation and scaling of the panels.
3. Diagnostic solid red and blue textures to inspect channel handling.
4. Opaque blue followed by overlapping half-alpha red, depth disabled.
5. Nearer opaque red drawn first and farther opaque blue second, depth enabled.

The depth stage uses different aspect ratios; blue may be visible beyond the
red panel. Judge the overlapping region. Labels are CPU framebuffer text after
GPU synchronization, so they are not evidence of text rendering by the GPU.
Existing lighting shader code is retained. Its source multiplies RGB by the
normal/light dot product and preserves sampled alpha. Exact unlit color
calibration, gamma behavior, G_MTX decoding and additional formats remain
unfinished. SDK transforms are not presented as game matrix-command support.
Solid colors and alpha values are explicitly diagnostic resources.

```sh
source xbox360/xenon_env.sh
python3 xbox360/startup_probe.py --prefix "$DEVKITXENON" --diagnostic graphics-suite
```

Output: `build/xbox360/graphics-suite-testing/xenon.elf`, already packaged for
XeLL. Host tests are mandatory in the builder. They check both child draws and
binding changes, 17 total commands, truncated parent/child resources, unknown
opcode/missing resource rejection, cyclic recursion limit and missing END.
Exact commands/results are saved in the output directory. Local strict C
syntax, generated harness syntax and Python syntax checks pass. Native
linking, host test execution and all new stages await the user's Ubuntu build
and console execution. Existing single/multi targets remain available.

Report each stage independently; success of one does not imply all five pass.
A short video across the complete 50-second cycle is more informative than
a single frame. No game/XEX execution is claimed.
