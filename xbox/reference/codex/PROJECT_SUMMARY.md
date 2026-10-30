# Animal Crossing — Native Xbox 360 Port: Project Summary

**Status date:** October 30, 2026  
**Source project:** [ACreTeam/ac-decomp](https://github.com/ACreTeam/ac-decomp)  
**Current runtime:** libxenon / XeLL-compatible PowerPC ELF  
**Intended final deliverable:** Playable Xbox 360 XEX  
**Current major milestone:** 3 — Original startup and first integrated screen

## Current position

We have built a substantial Xbox 360 port framework and verified several pieces
on a real console. **The complete Animal Crossing startup and playable game loop
are not working yet.** Successful diagnostic screens and selected original actor
callbacks must not be confused with a working game.

There is no defensible overall completion percentage. The next major visible
achievement is an original game screen reached through the original startup flow,
rather than through a diagnostic harness.

This document consolidates the work and conversation so far. Detailed reports
linked below contain narrower implementation limits and supporting evidence.
Historical reports describe their state at the time; later reports can supersede
those details. This summary is not a fresh whole-repository audit or a new claim
that all previously compiled objects still form a complete executable.

## Project approach and constraints

- Compile the original C/C++ game code for Xbox 360 PowerPC where practical.
- Replace GameCube-specific services behind compatible interfaces.
- Keep the original GameCube build path separate from Xbox-specific work.
- Preserve compatible big-endian representations; avoid blanket byte swapping.
- Validate serialized resource bounds, object layouts, alignment and ownership.
- Prefer executable, tested increments over speculative SDK implementations.
- Label incomplete behavior and reject unsupported operations explicitly.
- Do not claim console execution based only on compilation or host tests.

GameCube and Xbox 360 are both big-endian PowerPC platforms in this work, but
sharing endianness does not make their operating systems, GPUs, instruction
extensions, clocks, device interfaces or startup environments interchangeable.

The current graphics backend uses **libxenon's Xenos interface**, not Direct3D.
A future XEX runtime/toolchain still needs to be established. An ELF cannot be
turned into a working XEX simply by renaming it or changing its container.

The PC port follows a similar source-port strategy with a different graphics
backend. Its GX-to-OpenGL implementation can inform behavior, but its OpenGL
calls and shaders do not directly run through the current Xenos backend.

## Five major milestones

| Milestone | Assessment |
| --- | --- |
| 1. Asynchronous resource loading | Implemented and tested for supported paths; game-wide completeness is not established |
| 2. An original game resource loader | Original loader components integrated for supported resources; not every game resource/loading path is verified |
| 3. Original startup and a first integrated screen | **In progress** |
| 4. A functioning game loop | Selected actor, scene and scheduling pieces exist; full integration remains |
| 5. Playable XEX build | Not established |

Milestone 4 includes actors, scene transitions, controller input and game audio.
Milestone 5 also requires an appropriate XEX runtime/toolchain, wireless input,
saving/loading and sustained gameplay validation.

## Repository audit and build preparation

Work established a separate Xbox 360 target, compiler compatibility changes,
source/dependency investigations, object/archive probes, layout checks and
GameCube-path guards. Startup code, platform dependencies, original resource
loading and module boundaries have been investigated.

Important areas identified include GameCube OS services, interrupts, low-memory
addresses, GX/VI graphics, DVD access, controllers, audio, startup and REL linking.
The original PowerPC target alone does not make those implementations reusable.

The project contains compatibility inventories and compiler/link diagnostics.
Those reports are evidence for specific sweeps/builds; they are not proof of a
complete game link. Static archive construction and individual source compilation
are distinct from resolving the entire executable and its runtime dependencies.

**Foresta/actor RELs:** static source linking remains an investigated engineering
route, not a completed whole-game integration. The foresta load/entry handoff and
subsequent startup still need work. Neither sharing a CPU family nor compiling an
archive proves that dynamic module behavior, constructors or lifetime rules can
be removed safely.

References: [audit](../AUDIT.md), [continuation history](../CONTINUATION.md),
[file compatibility inventory](compatibility.csv),
[port references](PORT_REFERENCES.md).

## Development environment and build workflow

The desktop chat remains in Windows. Builds requiring the GNU Xenon toolchain
are performed manually in Ubuntu WSL. Earlier WSL access/path problems motivated
this workflow; switching the chat environment is not required.

Typical commands, from the repository root in Ubuntu WSL:

```sh
source xbox360/xenon_env.sh
python3 xbox360/startup_probe.py --prefix "$DEVKITXENON" --diagnostic TARGET
```

Use a documented diagnostic name in place of `TARGET`. Output is normally under
`build/xbox360/TARGET-testing/`. The build script packages a fresh ELF using the
XeLL address convention and checks its load ranges and undefined symbols.

The earlier “ELF is too large” failure occurred during loader handling despite
the file being relatively small. ELF load addresses/memory ranges matter as well
as file size. Always use the packaged output specified by the build instructions;
do not substitute an intermediate object or a minimal link-check ELF.

Local Windows checks use Zig's Clang/LLD for PowerPC compilation and WASM/Node
for executable host tests. These do not substitute for the GNU SDK/CRT final link
or for actual PowerPC execution on a console.

## Console-confirmed progress

The following was reported by the user during the diagnostic sequence:

- Native startup reached main, initialized video and displayed framebuffer text.
- An audible diagnostic beep occurred; this does not establish game audio support.
- GPU clearing eventually produced the expected white output after investigation.
- A spinning textured cube (“cube-ception”) rendered.
- Original inventory-panel geometry and GC texture panels rendered.
- USB-loaded resource diagnostics succeeded, including integrity checks.
- Original-resource, animation and presentation diagnostics progressed successfully.
- Train-door animation became smooth in the revised timing test.
- The normal-depth glass view showed glass through the window opening, behind
  the solid door frame.
- The relevant presentation fixes removed the reported tearing/strobing.
- Actor-batch and actor-model-batch stages were reported successful with expected
  final values.

Earlier broad “passed” reports apply to their respective diagnostics. They do
not automatically verify later code changes. The latest ownership/material/GX
additions have local tests and PPC compilation, but no new console confirmation.

A wired-controller test could not be completed because the user has wireless
controllers only. Wireless support is still a later runtime/input requirement;
the project has not established that the final port must require wired input.

See the [console checkpoint ledger](CONSOLE_CHECKPOINTS.md).

## Implemented subsystems

### Scheduling, timing and startup services

- Cooperative fibers, message queues, mutexes and frame acknowledgements.
- Timer conversion between the native Xenon timebase and GameCube clock units.
- A bounded one-shot menu timer with explicit full-queue retry/cancellation rules.
- Safe completed-thread retirement and reuse; live cancellation is not fabricated.
- Production menu thread and JKR allocation bindings prepared and PPC-compiled.
- Failed fences or unfinished work do not silently grant permission to release
  resources.

The cooperative scheduler is not a general replacement for Dolphin preemption,
interrupt handling or every OS service.

### Storage and original resource loaders

- Read-only FAT32 USB access, including superfloppy/MBR and cluster-chain handling.
- Raw GameCube disc-image/FST access and DVD-style resource interfaces.
- Queued/asynchronous resource work and completion delivery for supported paths.
- Resource length/integrity checks and streamed/external test resources.
- Supported paths through original JKRDvdFile, DVD ripper, decompression,
  archives and JKR heap implementations.

Original encoded asset bytes are retained where suitable. Platform differences
are handled at interpretation/upload boundaries. Existing formats are not
universally declared supported merely because they can be extracted.

### Actors and scenes

- Original train-door construction, movement, drawing and destruction callbacks.
- Keyframe animation and selected model/material dispatch.
- Scene ownership, original actor-list operations and checked traversal.
- Deferred removal so a traversal does not immediately free the actor being visited.
- Resident preparation before frame traversal, including reload boundaries.
- Immutable model caching, heap/lifetime checks and original callback timelines.

These are selected integrations, not the full actor manager or functioning town
simulation. Game audio events captured by diagnostics do not prove audio playback.

### Display lists and presentation

- A bounded interpreter for selected Animal Crossing/F3DEX-style display lists.
- Matrices, selected geometry commands and original resource slices.
- Texture, blending/depth and glass diagnostics.
- Presentation and pacing changes verified by the user in the relevant builds.

The interpreter still does not provide complete GX/emu64 behavior or a general
replacement for every original shader, fog, lighting or framebuffer operation.

## Original startup investigation

There are separate startup roles that must not be confused:

1. The boot-side `src/static/boot.c` main initializes platform/framework services,
   runs the initial menu and loads resources including foresta.
2. Foresta's `src/main.c` main installs the hot-start entry.
3. That entry proceeds through mainproc, graph_proc and game initialization.
4. First-game/second-game startup introduces additional resource and audio
   readiness requirements before later screens.

The earliest original boot-logo emitter and its assets have been compiled and
executed in a host reference path. The actual initial-menu initialization, worker
loop and cleanup complete in a controlled host backend: three normal runs took
336 simulated frames each, and allocation-failure cases cleaned up correctly.

This is not production native-thread execution or a completed original startup.
The controlled backend's simulated module-load completion is not proof that
foresta loaded or that the game reached its title screen.

Menu frame/fade submission, real lifecycle ownership, timer pumping, safe queue
reset/join behavior and the foresta handoff still need integration. Audio
readiness must not be faked simply to advance startup.

References: [startup screen audit](ORIGINAL_STARTUP_SCREEN.md),
[menu lifecycle](BOOT_MENU_LIFECYCLE.md),
[production services](BOOT_PRODUCTION_SERVICES.md).

## Selective Aurora adaptation

[Aurora](https://github.com/encounter/aurora) is useful as a source-level
GameCube/Wii compatibility reference. Its current renderer depends on
WebGPU/Dawn and modern platform facilities; we have not ported that runtime.

We selectively adapted CPU texture algorithms instead:

- All eleven regular GX formats: I4, I8, IA4, IA8, RGB565, RGB5A3, RGBA8,
  C4, C8, C14X2 and CMPR.
- All three TLUT formats: IA8, RGB565 and RGB5A3.
- Correct padded tile accounting, explicit serialized-byte reads, bounded output
  pitch/capacity and overlap checks.
- Visible palette-index validation before output writes.
- ResTIMG metadata parsing, mip accounting and palette/image extent validation.
- BGRA conversion for the established upload path.

MIT attribution is preserved in `xbox360/third_party/aurora/`. The provenance file
records inspected URLs and adapted components. It does not claim a pinned full
upstream revision or direct execution of an upstream Aurora binary.

The shared decoder now serves the existing train CI4/I8 path. Its prior reference
pixels remain unchanged. Intensity alpha semantics are kept distinct from the
material/combiner operation that consumes those texels.

References: [Aurora adaptation](AURORA_ADAPTATION.md),
[common texture formats](GX_COMMON_TEXTURES.md),
[ResTIMG loading/upload](TIMG_RESOURCE_UPLOAD.md).

## Latest GX ownership and material integration

The newest component connects:

```text
Registered immutable resource spans
    -> source-level GX texture objects and TLUTs
    -> checked stage bindings and frame pins
    -> constant-input material conversion
    -> native Xenos texture cache and drawing
    -> completion fence
    -> owner retirement
```

- GXTexObj remains 32 bytes; GXTlutObj remains 12 bytes.
- Opaque values carry checked generation tokens/offsets. Ordinary object copies
  remain valid and independent; stale generations fail.
- Rebinding does not release resources used earlier in the current frame.
- The native backend installs real Xe_Sync completion fencing.
- A bounded 32-surface cache keys resource generations, formats, samplers,
  palettes and material constants. It does not retain raw asset pointers.
- Shared material programs cover texture replacement, constant modulation and
  the verified train opaque/glass formulas.

These are source-port opaque values, not original GX hardware register words.
The facade replaces a documented subset of GXTexture.c; it must not be mixed
with original methods that read that private packed representation.

The material programs currently bake constant inputs into textures. They are
not a general or bit-exact TEV implementation. Varying vertex colors, arbitrary
TEV equations, multi-texture materials and full lighting/fog need shader work.

Native mip sampling remains unsupported: the pinned SDK's texture creation code
ignores its levels argument. CPU mip accounting does not establish GPU mip support.

Reference: [GX texture ownership/material report](GX_TEXTURE_OWNERSHIP.md).

## Recent local validation

These figures describe specific local tests, not an overall game completion score:

| Check | Verified result |
| --- | --- |
| Earlier RGBA8/CMPR vectors | 633 cases, about 2.37 million texels |
| Additional direct/indexed formats | 840 cases |
| RGB5A3 helper | All 65,536 values match prior reference |
| Palette expansion | 196,608 words: all 65,536 values in each of three TLUT formats |
| ResTIMG resources/mips | 29 generated resources, 117 decoded levels |
| Malformed resource rejection | 530 cases |
| Ownership/material/native-contract groups | Nine groups in three fresh WASM instances: 27 passing runs |
| Train materials | Existing extracted reference pixels and render-state checks pass |
| Resident/actor regressions | Ownership, traversal, model cache, preparation and original callback checks pass |
| Compilation | Relevant code, original layout assertions and generated diagnostic sources compile for PPC |

Native SDK-call recorders use real SDK types/prototypes but are test-only
implementations. They verify control flow, byte handling and contracts; they do
not establish actual USB, GPU or PowerPC execution.

Typical local commands from the repository root:

```sh
python3 xbox360/test_gx_texture_binding.py --zig /path/to/zig --console-objects
python3 xbox360/test_gx_texture.py --zig /path/to/zig
python3 xbox360/test_timg_resource.py --zig /path/to/zig --console-objects
python3 xbox360/test_resident_scene_host.py --zig /path/to/zig --ppc
python3 xbox360/test_boot_menu.py --zig /path/to/zig
```

Requirements and fixture dependencies are documented by each runner/report.
Some Linux fiber lifecycle tests still require execution in WSL. Earlier native
Windows Zig linking attempts failed; successful PPC object compilation is a
separate result from those Windows executable-link attempts.

## Optional batched console checks

To reduce power cycles, diagnostics are batched rather than requiring a separate
boot for every small feature. Development continues without waiting for them.

The newest texture-specific build recipe is:

```sh
source xbox360/xenon_env.sh
python3 xbox360/startup_probe.py --prefix "$DEVKITXENON" --diagnostic gx-texture-owned
```

After a successful GNU build, the expected packaged file is:

```text
build/xbox360/gx-texture-owned-testing/xenon.elf
```

Use it as USB-root `xenon.elf`. Its synthetic texture resources are embedded.
The six comparisons are RGBA8 opaque/alpha/linear-alpha, then CMPR
opaque/alpha/linear-alpha, roughly eight seconds each. Stage submission and owner
release are checked before the final message. Visual accuracy remains a separate
review. No input controller or automatic reboot is required.

This target has been prepared and PPC-compiled locally; **its GNU final link and
console run have not been performed here**. It supersedes the older timg-texture
check for the next optional texture-specific launch.

The resident-scene cumulative checkpoint and other deferred checks remain in
[CONSOLE_CHECKPOINTS.md](CONSOLE_CHECKPOINTS.md). Do not launch a host test WASM,
intermediate object, or the minimal boot-emitter link-check ELF on the Xbox.

## Remaining work

### Immediate engineering tasks

1. **Connect real resource allocation lifetimes.** Register actual JKR/archive
   payloads and emu64 conversion buffers at known extents. Retire before free,
   stage mutable buffers safely and avoid guessing allocation sizes from pointers.
2. **Implement broader material/GX rendering.** Capture real TEV state and
   generate/select shaders for observed equations and varying raster inputs.
   Complete remaining texture/draw/framebuffer interfaces with explicit semantics.
3. **Complete original startup integration.** Wire original JW frame/fade
   submission, production menu services, foresta loading/entry and graph/game
   startup through the verified memory and scheduling boundaries.

### Later major requirements

- A complete, sustained game loop with full actors and scene transitions.
- Game audio playback and honest readiness/initialization behavior.
- Wireless controller support in the intended final runtime.
- Save/load and storage behavior under the final deployment model.
- A functioning XEX toolchain/startup path.
- Performance, correctness and long-session console testing.

## Detailed report index

### Startup, build and platform

- [Original startup and screen audit](ORIGINAL_STARTUP_SCREEN.md)
- [Original menu lifecycle](BOOT_MENU_LIFECYCLE.md)
- [Production boot services](BOOT_PRODUCTION_SERVICES.md)
- [Hardware diagnostics](HARDWARE_DIAGNOSTICS.md)
- [Port comparisons/references](PORT_REFERENCES.md)
- [Deferred console checkpoints](CONSOLE_CHECKPOINTS.md)

### Storage and resources

- [Storage diagnostic](STORAGE_DIAGNOSTIC.md)
- [DVD scene](DVD_SCENE.md)
- [Streaming](DVD_STREAM.md)
- [Asynchronous DVD work](DVD_ASYNC.md)
- [Original game resource loading](GAME_RESOURCE.md)
- [JKR file integration](JKR_FILE.md)
- [Game heap](GAME_HEAP.md)
- [DVD ripper](DVD_RIPPER.md)
- [Archives](ARCHIVE.md)
- [Game scene resources](GAME_SCENE.md)

### Actors, animation and presentation

- [Animation](ANIMATION.md)
- [External animation resources](EXTERNAL_ANIMATION.md)
- [Train materials](TRAIN_MATERIAL.md)
- [Actor motion](ACTOR_MOTION.md)
- [Original train actor batch](TRAIN_ACTOR_BATCH.md)
- [Actor model dispatch](ACTOR_MODEL_DISPATCH.md)
- [Scene ownership](SCENE_ACTOR_OWNERSHIP.md)
- [Scene traversal](SCENE_ACTOR_TRAVERSAL.md)
- [Resident preparation](RESIDENT_SCENE_MILESTONE.md)
- [Presentation](PRESENTATION.md)
- [Batch pacing and glass](BATCH_PACING_GLASS.md)

### Graphics compatibility

- [Display lists](DISPLAY_LIST.md)
- [Graphics suite](GRAPHICS_SUITE.md)
- [Matrix diagnostic](MATRIX_DIAGNOSTIC.md)
- [Original frame](ORIGINAL_FRAME.md)
- [Aurora selective adaptation](AURORA_ADAPTATION.md)
- [Common GX formats](GX_COMMON_TEXTURES.md)
- [ResTIMG loading/upload](TIMG_RESOURCE_UPLOAD.md)
- [GX ownership and material integration](GX_TEXTURE_OWNERSHIP.md)
