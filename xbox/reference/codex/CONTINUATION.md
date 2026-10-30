# Static-target and SDK preparation continuation

The initial audit remains a historical baseline. This continuation adds verified compilation coverage, an authoritative static-source manifest, target-specific compiler fixes, and an SDK-header graphics diagnostic. None of these results establish console execution.

## Build manifest and lifecycle

`static_target.py` reads `config/GAFE01_00/foresta/splits.txt` in its original order, validates every source path, records the split hash, and lists per-source language, role and entry rename. There are **3,777 source units**: 559 non-data game units, 3,217 data/furniture/bg-item units, and executor.c requiring replacement. The default sweep compiles the 559 game units plus `static_lifecycle.c`. The resource manifest contains 16,367 contiguous symbol/binary/header entries from the original extraction configuration, across DOL and REL resources. It is a required-resource inventory, not a complete asset extractor or proof those resources are available.

`static_lifecycle.c` replaces the REL prolog's game-entry registration with a guarded native call to `ac_foresta_main`. Native CRT owns C++ initialization/destruction. Shutdown is rejected while HotStartEntry remains active. It does not replace boot.c's LoadLink calls yet, run constructors itself, free game resources, execute a tick, or implement the platform scheduler. Wiring the static lifecycle into boot remains dependent on the full resource/runtime integration.

## Compiler fixes

- Target-only intrinsic mappings for `__abs` and `__alloca` use compiler builtins.
- Xbox branches in `include/graph.h` remove redundant Gfx* casts that prevent assignments to the already typed `thaGfx.head_p` lvalue. Structure representation and increment units remain unchanged.
- Xbox branches in graph.c and m_warning_ovl.c use valid token concatenation: member access remains `.name`, while only identifier suffixes are pasted.
- Six implementation files give private function forward declarations the same static linkage as their definitions, under the Xbox target only. Existing header-declared external symbols were not made static blindly.
- Two legacy implicit-int declarations now specify int on Xbox, and FORCESTRIP uses a real compiler section attribute on this target.

The GameCube branches retain exact upstream text. `check_gc_guards.py` removes the Xbox conditional branch and compares all 12 modified files byte-for-byte after normal text newline decoding with `git show HEAD:path`; it passes. This structural check is not an original GameCube binary rebuild. The smoke/layout tests are rerun after the shared-header modifications.

## Compile results and symbol inventory

First full sweep: 527 passing, 33 failing. The first compatibility pass reached 535 passing, 25 failing, from 560 selected units. Further declaration fixes and a complete rebuild are recorded in `static-symbols.json` and `static-compile-results.json`, which hold the final counts and every command/diagnostic; `static-initial-results.json` preserves the first sweep. All archive objects are checked as PPC32 BE relocatable ELF. The symbol inventory uses global/weak entries only; local definitions cannot incorrectly satisfy another unit's import. This is symbol-table triage, not an active-relocation analysis or final link. Data symbols and definitions from failed/uncompiled units are included among the candidates.

Final complete rebuild: **544 passing, 16 failing**. Eleven failures are missing extracted assets; five retain declaration/return problems requiring further review. The partial archive contains all 544 passing PPC32 BE relocatable objects, verified individually, with 4,877 unresolved symbol candidates across successful units. Input allocation sections total 3,843,828 code bytes, 61,761 read-only bytes, 245,963 writable bytes and 2,304,931 BSS bytes. The archive file is 7,695,824 bytes; these figures are not a complete game memory footprint.

Remaining compiler blockers include missing generated asset headers, mismatched static/non-static forward declarations, implicit-int source and missing values in non-void returns. The latter are not silenced: they require gameplay/control-flow review to choose correct behavior. No dummy asset arrays or success-returning hardware stubs are supplied.

`foresta-partial.a` is an archive of successful objects only. `static-archive.json` records object count, archiver return code and content hash. This proves archive construction, not that the complete game resolves or loads. No platform/runtime/data library was linked into a console executable.

`check_archive.py` verifies every ELF member's machine, byte order, class and relocatable type. It sums input allocation-section bytes into code/read-only/writable/BSS categories. These totals exclude the omitted units, SDK, resources, linker padding and all runtime allocations; they are a preliminary input-size measurement, not a console memory budget.

## Actual libxenon graphics boundary

The diagnostic includes the genuine pinned `xenos/xe.h` and `xetypes.h`, without GC headers. It compiles to a PPC32 BE object using `Xe_Init`, `Xe_GetFramebufferSurface`, `Xe_SetRenderTarget`, `Xe_SetClearColor`, `Xe_Clear`, `Xe_Resolve`, `Xe_Execute` and `Xe_Sync`. The call sequence was inspected against xe.c's implementation. The first compile failed on missing Clang standard `stdbool.h`; supplying the embedded compiler's real resource directory fixes it without fabricating SDK types. `sdk-probe.json` records command, commit and undefined SDK symbols.

The diagnostic requires a valid display mode and libxenon CRT before being called. Clear color is deliberately specified as an SDK word; GXColor channel mapping, display pacing and visual output remain unverified. A textured triangle/TEV path needs compiled Xenos shaders and hardware validation; it has not been implemented from guessed shader bytecode. Audio, OS queues and thread adapters remain unimplemented.

## Environment limits and next work

`toolchain-status.json` records that xenon-gcc and Docker were not found. The user confirms WSL is installed; subsequent status/list commands return Wsl/E_ACCESSDENIED in this Codex session, so its distributions and toolchains remain uninspected. The pinned libxenon build recipe is Linux-oriented and downloads unverified dependency artifacts; merely pinning the repo commit would not make it reproducible. No system-wide WSL installation or toolchain substitution was performed. The real xenon ABI fixtures, CRT link, console log capture and memory budget still require a suitable build/execution environment.

Next practical steps are to supply the original disc extraction, fix the remaining semantic/compiler blockers, then link against pinned devkitxenon/libxenon with actual OS/DVD/input adapters. Once that environment is available, execute the clear diagnostic before implementing a GX texture/TEV adapter. The original audit's final-link and execution limitations remain in force.

## Ubuntu native-toolchain continuation — 2026-10-10

This session inspected Ubuntu 26.04.1 under WSL2. No xenon-gcc or installation under `/opt` was found, and the host compiler/build dependencies were initially missing. `sudo -n apt-get update` failed with `sudo: interactive authentication is required`; the user then installed the requested dependencies. Exact package versions, environment inspection and URL results are retained in `report/xenon/environment.json`.

### Toolchain installed

The existing libxenon pin `c32c813c3d630ae922f83395ee4509b0468af71d` was cloned and inspected. The recipe's GCC 16.2.0 mirror URL actually returned HTTP 200; it was not an absent download. This build selected GCC **9.2.0** with its matching Xenon patch, binutils **2.32**, and newlib **3.1.0**. All selected URLs returned HTTP 200, all archive/patch hashes were checked, and the patches applied with zero fuzz. The lock records locally captured HTTPS hashes; publisher signatures were not independently verified.

`install_toolchain.py` runs the reviewed configure/make stages without executing the upstream shell script. It omits the upstream automatic sudo/chown/cleanup, `/opt/local` dependency assumptions, optional downloads and unpinned filesystem repositories. Host GCC 15.2.0 uses GNU++11 and `-fcommon` for the older toolchain sources. Binutils, C bootstrap compiler, newlib, final C/C++ compiler and libxenon all built and installed with exit code zero. No additional SDK source patch was needed. The SDK tracked-source diff remains empty.

The installation was built at `/tmp/ac-devkitxenon` and retained at **`build/xbox360/devkitxenon`**. The relocated compiler, C++ compiler, PPC32 libgcc and CRT lookup were checked. `source xbox360/xenon_env.sh` selects it without editing shell startup files. `report/xenon/toolchain/stages.json` records exact commands, directories, environment, exit codes and durations, with raw retained stage logs alongside it. See `TOOLCHAIN.md` for downloads and rebuild commands.

### ABI and compilation

The existing **five smoke objects pass** with xenon-gcc, `-m32 -maltivec -fno-pic -mpowerpc64 -mhard-float`. Layout assertions and all four symbol-byte fixtures pass: endian `12345678`, float `3f800000`, RGB5A3 `0000ffff`, bitfield `123456789abcdef0`. The actual endian macro override is rejected by the endian guard. Actual `-m64` compilation is rejected by the pointer/long/layout assertions. These are compilation/object inspections, not executed numerical tests.

The SDK-only graphics probe also compiles successfully with GCC against the genuine pinned headers. Broader probes compile boot.c, main.c, the actor table, ac_ant.c, m_card.c, aictrl.c and GXFifo.c; executor.c, GC startup/DVD and the emu64/jsyswrap C++ probes still fail. GXFifo compilation includes implicit hardware-intrinsic warnings and unresolved imports; it does not establish a working hardware path. Full diagnostics, including the actual linker invocation from the broader probe, are in `report/xenon/probes.json`.

Both complete native sweeps compile **505 of 560 selected units; 55 fail**. For consistent review, GCC's `-Werror=return-type -Werror=implicit-int` keeps invalid return/declaration behavior visible rather than accepting it as warnings. GCC 9 additionally rejects unnamed parameters in C function definitions. The final failing-unit groups are:

| First blocking category per unit | Units |
|---|---:|
| Missing extracted asset headers | 11 |
| Unnamed C parameters | 24 |
| Non-void functions with missing/invalid returns | 17 |
| Conflicting static/external declarations | 3 |

The original 544/560 Windows result is preserved in the earlier reports. The native result uses a different compiler and explicit return diagnostics; it is not a claim that 39 previously working runtime units regressed. No gameplay source, generated assets or hardware stubs were added to force units to pass.

The first native sweep used GNU11 at default optimization. A second sweep used **`-fgnu89-inline -O2`**, retaining the same blockers. It was a diagnostic experiment in legacy math-header emission, not a fix. Its archive is the current `build/xbox360/xenon/static/foresta-partial.a`: **505 individually verified ELF32/PPC/big-endian relocatables**, **6,282,180 bytes**, SHA-256 `77b519fc7b187812d5cb9858cc416ed9deaccc62016969bb7994e27666c2f6ac`. Input sections total **2,303,248 code**, **674,929 read-only**, **126,755 writable**, and **1,892,854 BSS bytes**. These omit COMMON symbols, failed/data units, SDK, resources, linker padding and runtime allocations. Symbol-table triage finds 4,666 external candidates; this is not the final linker's unresolved count.

`report/xenon/initial-*` retains the first native compilation/link evidence; unsuffixed native reports retain the optimized experiment. All commands and per-unit diagnostics are in the corresponding JSON. To reproduce the experiment, append `-fgnu89-inline -O2` to the documented build/static flags and pass `--game-flags='-fgnu89-inline -O2'` to `link_probe.py`. The math-header policy remains unresolved; do not treat this flag as a remedy.

### Actual CRT and game links

All these attempts used the actual installed compiler/linker, libxenon CRT, pinned `app.lds`, PPC32 newlib/libgcc and libxenon library. No linker option was used to permit duplicate definitions or unresolved symbols.

| Link | Result |
|---|---|
| SDK-only CRT plus genuine Xenos probe object | **Exit 0**, native executable linked |
| First qrand/arena/game-header smoke | Exit 1: duplicate `fabs`, `sqrt`, `sqrtf`; undefined `__float_nan`, `__float_huge` |
| First whole partial-game archive | Exit 1: duplicate math definitions and **4,656 distinct undefined symbols** |
| Optimized/GNU89-inline smoke | Exit 1: duplicate `fabs`, `fabsf`, `__fpclassifyf`, `__fpclassifyd`; undefined `guMtxIdentF` |
| Optimized/GNU89-inline whole partial-game archive | Exit 1: duplicate math/helper definitions and **4,653 distinct undefined symbols** |

The SDK-only artifact is **`build/xbox360/xenon/sdk-only.elf`**, 1,376,480 bytes, SHA-256 `edeadd090d2b0e171730c0b2f5872fd6f8e6dd27db8e4d3bf00687ba53149f33`. `xenon-readelf` reports ELF32, big endian, PowerPC, EXEC, entry **`0x80002300`**; `xenon-nm -u` lists no undefined symbols. It links the genuine graphics probe but its standalone main only prints a diagnostic message. It does not initialize or execute that graphics probe, load game resources or start the game. Loader packaging and console execution were not tested.

The whole-archive audit uses a diagnostic entry solely to root all passing game objects. It is not a replacement for GameCube boot. Undefined symbols include game assets/profile definitions, Dolphin OS queues/threads/alarms, GX/DVD/PAD/CARD, JAudio/Na and high-level static support. The failed or excluded units can supply some of them; hardware interfaces still require real implementations. Raw linker diagnostics, exact commands, parsed distinct symbol names and ELF inspections are in `report/xenon/{initial-links,links,summary,sdk-elf-checks}.json`. Distinct counts are parsed from actual linker diagnostics, not the archive's candidate symbol list.

### Preservation and remaining work

All 12 pre-existing shared-source/header changes remain intact. The original GameCube branches again compare exactly with upstream through `check_gc_guards.py`; `configure.py --help` passes. This session adds Xbox build tooling, diagnostics and reports without editing gameplay or GameCube configuration. An original GameCube binary rebuild remains unavailable without the disc/extraction.

Next work is a reviewed target-only math/header linkage policy, names for otherwise unused C parameters, and semantic review of return/linkage blockers, followed by real extracted resources and platform adapters. Preserve the failed link evidence while resolving these imports. **No Xbox 360 execution, qrand/arena runtime result, game tick, display output, audio, input or save behavior has been tested.**

## Compilation comparison and compatibility repair

The 544/560 and 505/560 logs have now been compared by source filename. All three historical sweeps selected the same 560 unique units in the same order, with identical manifest roles/languages/entry renames and split hashes. The 39 newly failing units comprise **24 unnamed-parameter C23 extensions** accepted with warnings by Clang and rejected by GCC 9, plus **15 existing missing-return warnings** promoted by the native `-Werror=return-type` flag. The earlier count comparison changed diagnostic policy as well as compiler; these fifteen failures were not newly discovered source defects. All original per-unit and aggregate build logs are preserved, with hashes.

The review and exact per-file diagnostics are in [report/comparison/INVESTIGATION.md](report/comparison/INVESTIGATION.md). Compiler version/target probes, exact options/include paths, historical-input limitations, pre-edit source hashes/archive, relevant source diffs and copied logs are retained alongside it.

Xbox-only compatibility edits name 47 unused parameters in 40 definitions and reconcile 13 linkage declarations/definitions. Bodies, parameter types, real data initializers, headers and previous Xbox changes are preserved. The GameCube branch check now passes for all 38 modified files. No guessed returns, suppressed errors or dummy assets were added.

The complete strict rerun, using the **first native build's unchanged flags and error policy**, reaches **530/560**: 25 previous native failures now pass, and no previous native passes are lost. The remaining **30 failures** are **11 missing-asset units and 19 missing/invalid-return units**; removing earlier compatibility blockers exposed additional return errors in m_collision_obj.c and Totakeke. Both deserve control-flow/return-contract review rather than invented default values.

New reports are isolated under `report/comparison/fixed/` and build products under `build/xbox360/comparison/fixed/`. The partial archive contains 530 verified ELF32/PPC/BE relocatables, 9,013,214 bytes, SHA-256 `9db7b7ea0cb4d83e74e23a4b6281d8a52f8cc985a96ab667a62b2a05587eaba0`. It remains incomplete and unlinked. All five layout/smoke objects, all four fixture bytes and both intended negative endian/PPC64 guards pass again. No new link or console execution was attempted during this investigation.

## Disc-backed assets and return-contract repair

The supplied USA Rev 0 disc image now verifies against SHA-1
`2d2b1fa3883f49af779ce9ca133db3be17be8f32`. The original configuration and
decomp-toolkit extraction produced real resources and 4,103 original objects.
All 5,068 existing custom asset conversion steps completed; the Xbox asset
target reuses the unchanged converters and binary inputs with a separate
include output directory. GameCube configuration remains unchanged.

Reviewed Xbox-only return contracts and parameter names now pass **560/560
of the same selected units**, retaining strict return/implicit-int errors.
The player unit exposed fourteen further unnamed parameters and five further
side-effect-only return defects after its assets became available; these were
reviewed and repaired rather than suppressed. Original submenu assembly
confirms its ambiguous early-return path retains the input function pointer.
All 66 modified shared files restore to upstream GameCube text, and seven
representative changed units compile with CodeWarrior outside the restricted
sandbox. Full rebuilt GameCube binary hashes have not been verified.

The 560-member archive is verified ELF32/PPC/big-endian, 11,187,294 bytes,
SHA-256 `b8fce9c2d4a72cffa4a7cb7c63ca8cf6a08047ad0c62cc51001270b52b756f9b`.
It still excludes 3,217 data/furniture/bg-item units and separate DOL/platform
support. All five ABI smoke objects, four byte fixtures and both negative
guards pass again. The real SDK-only CRT executable links without undefined
symbols, but the whole-game archive link fails on duplicate math definitions
and 5,819 distinct undefined symbols. No linker errors were bypassed and no
SDK or asset stubs were fabricated. No console execution has been tested.

Exact commands, diagnostics, preservation checks and reproduction steps are
in [report/returns-assets/REPORT.md](report/returns-assets/REPORT.md). Earlier
Windows/native/530 reports and archives remain intact. Next work is the
math/header linkage policy, required data/DOL compilation and genuine
Dolphin-to-Xenon platform integration.


## Full data build and native backend primitives

The integration continuation now passes **3,777/3,777** strict native foresta
game/data units, including the unchanged ordered selection of 560 earlier
units. Real disc assets are used throughout. Twenty-nine local vertex forward
declarations and narrow C++ compatibility issues have Xbox-only guards. All
104 changed shared files preserve their original GameCube text, and three
representative new changes compile with original CodeWarrior.

The final DOL source sweep uses the original C++ language choices for the
JAudio and emu64 .c files: **177/320** pass; 143 failures remain explicit.
Three additional .cp CodeWarrior runtime units were probed and are explicitly
excluded from the GCC archive policy. SDK-backed backend primitives link with
no undefined symbols. Host tests verify real disc reads, allocation and time
scaling; no hardware behavior has been tested.

Valid incremental whole-game links fail at 273, 258, 261 and 451 distinct
undefined references as support groups are added. The last group also exposes
three legacy absolute-address declaration duplicates. Earlier in-flight link
evidence was invalidated and preserved; the repeated links use the finished,
verified 3,777-member archive. The Dolphin scheduler, synchronization, game
platform bindings and hardware backends remain unfinished.

Full commands, per-source diagnostics, archive hashes, SDK interface limits
and preserved earlier evidence are in [report/integration/REPORT.md](report/integration/REPORT.md).

## Runtime continuation

The three absolute-address ownership collisions are resolved with Xbox extern
declarations and real owned state. The strict DOL sweep now passes **211/320**
(109 failures); all 3,777 game/data units still pass, including the same ordered
560. Four actual game link attempts have zero duplicates and still fail with
272/257/260/447 distinct undefined references. All earlier report hashes remain
preserved; GameCube branch restoration passes for 113 modified shared files.

Real cooperative scheduling/synchronization, raw-disc FST/synchronous DVD and
USB attachment/calibration foundations compile. Scheduler and Xenos/PCM/PAD
diagnostic ELFs link with empty undefined-symbol inventories. **No console is
connected; neither diagnostic has executed.** Dolphin preemption, game OS/PAD
bindings, verified console resource mounting, full DVD/FST lifecycle, GX/VI and
JAudio DSP backends remain unfinished. Do not mistake the foundations for a
working game runtime. Exact results and prerequisites are in
[report/runtime/REPORT.md](report/runtime/REPORT.md).
