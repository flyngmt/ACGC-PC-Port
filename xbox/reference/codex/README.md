# Xbox 360 preparation target

The game target is an isolated **object compilation and ABI smoke target**, not a playable port or finished libxenon integration. A separate SDK-only CRT diagnostic now links to a native ELF; it has not been executed. `configure.py` and GameCube configuration remain unchanged; shared source/header fixes are guarded by TARGET_XBOX360 and preserve the original GameCube branch text. Build outputs go to `build/xbox360`; audit evidence is under `xbox360/report`. See [TOOLCHAIN.md](TOOLCHAIN.md) for the pinned Ubuntu installation and [CONTINUATION.md](CONTINUATION.md) for native results and blockers. The [compilation investigation](report/comparison/INVESTIGATION.md) explains the 544/560 versus 505/560 difference and records the strict 530/560 compatibility rebuild without overwriting either baseline. The subsequent [disc-backed repair](report/returns-assets/REPORT.md) passes **560/560 selected units** with real extracted assets and reviewed return contracts; actual game links still fail on math definitions and unresolved imports.

From the repository root with Python 3 and Clang with a PowerPC backend:

```sh
python xbox360/build.py --cc clang
python xbox360/probe.py --cc clang
python xbox360/audit.py
```

The default compiler flags target `powerpc-none-eabi` (ELF32, big endian). This checks source representation, not the Xbox 360 executable ABI. Paths containing spaces must be quoted inside `--cc`, e.g. `--cc '"C:/Tools/LLVM/bin/clang.exe"'`.

Verified compiler used here: Zig 0.14.1's embedded **Clang 19.1.7**, invoked through `zig clang`, not `zig cc`:

```sh
python xbox360/build.py --cc "zig clang"
python xbox360/probe.py --cc "zig clang"
```

The compiler is not bundled with the deliverable. The tested download is [Zig 0.14.1 for Windows x86_64](https://ziglang.org/download/0.14.1/zig-x86_64-windows-0.14.1.zip).

For an installed devkitxenon compiler, this object-only invocation reflects flags in the inspected upstream devkitxenon rules. The Ubuntu GCC 9.2.0 build passes the layout and object byte checks with these flags:

```sh
python xbox360/build.py --cc xenon-gcc --flags="-DXENON -m32 -maltivec -fno-pic -mpowerpc64 -mhard-float"
```

Game boot, GX rendering, audio, scheduling and console loading remain unintegrated. The SDK probe uses genuine libxenon calls; the native diagnostic links use its CRT and application linker script. See `AUDIT.md` for the historical boundaries and `CONTINUATION.md` for later results.

`build.py` requires all five objects and then checks their ELF type and fixture bytes. `probe.py` records expected compiler/linker failures and verifies negative endian/64-bit guards. A zero exit from `probe.py` means the evidence was collected and negative guards worked; consult its JSON for individual results. `audit.py` inventories upstream tracked files only; it intentionally excludes untracked port additions and generated build output.

For the original GameCube build, continue using the upstream instructions: provide the supported disc image under `orig/GAFE01_00`, run `python configure.py`, then `ninja`. The supplied USA Rev 0 image is now verified and extracted, and seven representative changed units compile with CodeWarrior. A complete rebuilt DOL/REL hash match has not been verified.

## Static target continuation

```sh
python xbox360/static_target.py
python xbox360/static_target.py --cc "zig clang" --ar "zig ar"
python xbox360/check_gc_guards.py
python xbox360/check_archive.py
python xbox360/sdk_probe.py --cc "zig clang" --libxenon /path/to/libxenon --resource-dir /path/to/zig/lib
```

The manifest is based on the authoritative foresta split list, rather than globbing every source file. The default compilation covers non-data units and replaces executor.c with a native-CRT lifecycle unit; main.c is compiled with `main=ac_foresta_main`. `--include-data` attempts the data units too, requiring extracted resources. `--retry-failed` reuses passing objects only if a broad source/header fingerprint still matches. `--ar` archives passing objects as `build/xbox360/static/foresta-partial.a`; incomplete units and external symbols remain explicit in the reports. A zero exit records the sweep, including failed units; it does not certify a complete library.

The SDK diagnostic is intentionally compiled in a separate translation unit without GameCube headers. It uses actual Xe_* declarations, and requires libxenon startup/display initialization before execution. It is not wired into GX or game boot. See `CONTINUATION.md` for results and unresolved tasks.

## Native integration continuation

The strict native game/data build now passes **3,777/3,777** units. The original
560 remain in the same order and pass. The DOL sweep passes **177/320**, with
three additional CodeWarrior `.cp` runtime units separately probed and excluded
from the GCC archive policy. Real game audit links still fail; the SDK-backed
backend diagnostic links without undefined symbols but has not run on hardware.
See [the integration report](report/integration/REPORT.md) for exact diagnostics,
preserved logs, link groups, SDK contracts and the unfinished Dolphin scheduler.

```sh
source xbox360/xenon_env.sh
python3 xbox360/static_target.py --cc xenon-gcc --ar xenon-ar \
  --flags='-DXENON -m32 -maltivec -fno-pic -mpowerpc64 -mhard-float -fmax-errors=0 -Werror=return-type -Werror=implicit-int' \
  --include-data --jobs 4 \
  --asset-include-dir build/xbox360/returns-assets/assets/include \
  --out-dir build/xbox360/integration/static \
  --report-dir xbox360/report/integration/static
# Use --module dol and separate dol output/report directories for DOL triage.
# Wait for the archive command to finish before running links.
python3 xbox360/check_archive.py \
  --archive build/xbox360/integration/static/foresta-partial.a \
  --report-dir xbox360/report/integration/static
python3 xbox360/backend_probe.py --prefix build/xbox360/devkitxenon \
  --out-dir build/xbox360/integration/backend \
  --report-dir xbox360/report/integration/backend
python3 xbox360/tests/io_host.py
python3 xbox360/integration_links.py --prefix build/xbox360/devkitxenon \
  --build-root build/xbox360/integration --report-dir xbox360/report/integration
python3 xbox360/check_gc_guards.py \
  --report xbox360/report/integration/gc-guards-final.json
```

The backend exports real logging, allocation, monotonic ticks, registered-device
file reads, fresh USB packets and hardware worker tasks. It does not implement
the Dolphin OS scheduler, DVD/PAD contracts or game boot. Detailed restrictions
are documented in `native_backend.h` and the integration report.

The latest continuation resolves all three ownership collisions and reaches
211/320 strict DOL units while preserving the full 3,777-unit game/data build.
It adds cooperative scheduler, disc/FST and USB PAD foundations plus real linked
scheduler and AV/PAD diagnostics. These are not game OS bindings or a completed
GX/VI/audio implementation. No console is connected and no hardware execution
is claimed. See [report/runtime/REPORT.md](report/runtime/REPORT.md) for exact
commands, diagnostic artifacts and remaining blockers.

## Latest console diagnostic

Actor-motion and animation were reported successful by the user on October 20.
The next separate target loads the animated model from USB:

```sh
source xbox360/xenon_env.sh
python3 xbox360/startup_probe.py --prefix "$DEVKITXENON" --diagnostic external-animation
```

Copy xenon.elf, ACDVD.BIN and ACTRAIN.BIN from
`build/xbox360/external-animation-testing/` to the FAT32 USB root.
See [external animation report](report/EXTERNAL_ANIMATION.md) for expected results,
verified checks and remaining limits. The historical reports above describe
earlier milestones; the new mode has not yet been console tested.

The external-animation diagnostic was subsequently reported successful. The next
mode is `train-material`, which reads raw texture data and interprets the original
train material presets. See [train material report](report/TRAIN_MATERIAL.md) for
the build command, all three USB files, expected output and fidelity limits.

## Batched console checks

Train-material was reported successful. The new `batch-suite` mode combines six
numbered checks in one launch with automatic visual stages and a final summary.

```sh
source xbox360/xenon_env.sh
python3 xbox360/startup_probe.py --prefix "$DEVKITXENON" --diagnostic batch-suite
```

Copy xenon.elf, ACDVD.BIN and ACTRAIN.BIN from
`build/xbox360/batch-suite-testing/` to the USB root. No controller is required.
See [batch suite report](report/BATCH_SUITE.md) for stage descriptions and
validation limits. The combined target awaits console testing.

Batch v1 passed console counters/ownership, but motion stuttered and glass was
invisible. The same `batch-suite` command now builds v2 with presentation pacing,
a glass-facing view, three controlled glass views and final timing statistics.
See [batch v2 revision](report/BATCH_PACING_GLASS.md). Its hardware test is pending.

Batch v2 produced black isolated glass and a clear hole in the full door. The
same command now builds v3: side-by-side magenta/original16/expanded32 texture
controls, decoded-pixel CRC and mapped-upload checks, then full-door comparisons.
See [glass texture probe](report/GLASS_TEXTURE_PROBE.md). Hardware cause remains
unconfirmed; v3 awaits console testing.

User clarification: movement did not stutter in batch v2. Its pacing change is
console-verified by user observation; v3 preserves that pacing and investigates
only the unresolved glass rendering.

Confirmed console clarification: full-door glass remains visible through the
opening behind the frame with normal depth, as intended; depth OFF overlays the
wood as its control. Smooth pacing was also confirmed. These observations do
not require a further corrective build or repeat launch.

Next actor milestone: `--diagnostic actor-batch` runs original TrainDoor_Profile
callbacks inside the existing batch, with checked one-shot requests and captured
sound events. See [actor callback build/test instructions](report/TRAIN_ACTOR_BATCH.md).
The new target is locally compiled and its callback timeline host-tested; its
WSL final link and console run are pending. Earlier `batch-suite` remains available.

Console confirmation (2026-10-20): actor-batch passed with all expected final
counts. The next target is `--diagnostic actor-model-batch`; see
[actor model dispatch](report/ACTOR_MODEL_DISPATCH.md).

Console confirmation (2026-10-20): actor-model-batch passed with the expected
final values. Work now proceeds without waiting for further console runs.
See [deferred console checkpoints](report/CONSOLE_CHECKPOINTS.md) and
[scene ownership implementation](report/SCENE_ACTOR_OWNERSHIP.md).

Scene traversal is implemented and locally tested as `--diagnostic scene-walk-batch`.
This cumulative checkpoint includes the pending scene ownership/cache checks;
run only the newest checkpoint when convenient. See
[traversal report](report/SCENE_ACTOR_TRAVERSAL.md). Hardware confirmation is
recorded separately and does not block development.

Resident actor preparation milestone is locally complete as
`--diagnostic resident-scene-batch`. Every frame now validates both actors before
traversal, including reload boundaries. The actual C++ resource wrappers passed
host lifetime/failure tests and PPC compilation. This is the newest cumulative
console checkpoint; hardware verification remains deferred. See
[resident scene milestone](report/RESIDENT_SCENE_MILESTONE.md).

Major milestone 3 (original startup/first integrated screen) is in progress,
not complete. The real boot-logo emitter and original assets now have a native
`boot-logo` draw slice and locally executed reference renderer. Full original
menu/thread/module initialization remains to implement. See
[original startup screen audit](report/ORIGINAL_STARTUP_SCREEN.md).

Original menu initialization, worker-loop and cleanup now execute in a controlled
host test; GameCube-unit clock conversion and a one-shot timer are implemented.
This is host lifecycle verification, not a working native menu-thread backend.
See [boot menu lifecycle](report/BOOT_MENU_LIFECYCLE.md).

Selective Aurora adaptation (2026-10-29): bounded CPU GX CMPR/RGBA8 decoders and shared RGB5A3 expansion are implemented and host-tested/PPC-compiled. The train path uses the shared expansion with unchanged reference pixels. Full GX/upload integration is still pending. See [Aurora adaptation](report/AURORA_ADAPTATION.md); run test_gx_texture.py --zig /path/to/zig.

Original-format texture loading now validates ResTIMG headers/mip spans and supports a bounded native single-level upload path. Optional --diagnostic timg-texture batches six visual checks in one launch; no new hardware test blocks development. See [texture resource/upload](report/TIMG_RESOURCE_UPLOAD.md).

Common texture integration (2026-10-30): shared decoding covers eleven regular GX formats and IA8/RGB565/RGB5A3 palettes. ResTIMG and the train path now use the common boundary; prior train pixels remain unchanged. See [common textures](report/GX_COMMON_TEXTURES.md). Native GPU checks remain deferred.

GX ownership/material integration (2026-10-30): source-level texture facade preserves 32/12-byte objects, checks owned resource generations, pins frames through real native completion fences, and uses a bounded native cache with shared constant material programs. Optional --diagnostic gx-texture-owned batches the newer texture checks. See [ownership/material report](report/GX_TEXTURE_OWNERSHIP.md). Final GNU link and GPU execution remain deferred; milestone 3 is still in progress.
