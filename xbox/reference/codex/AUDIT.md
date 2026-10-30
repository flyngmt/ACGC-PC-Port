# Animal Crossing Xbox 360 technical audit

This document records the initial audit snapshot. See `CONTINUATION.md` for subsequent compilation, source fixes and SDK diagnostic work; the initial statement that all changes were additions no longer describes the current checkout.

Audit date: 2026-10-10. Upstream [ACreTeam/ac-decomp](https://github.com/ACreTeam/ac-decomp) commit `09ca8e8b5b24e6ab44047ee980cf0088ad7ecb4c`; comparison [flyngmt/ACGC-PC-Port](https://github.com/flyngmt/ACGC-PC-Port) commit `4099d246c927e75b4fd342ca13f4ac4395c55af5`; SDK reference [Free60Project/libxenon](https://github.com/Free60Project/libxenon) commit `c32c813c3d630ae922f83395ee4509b0468af71d`.

## Verified scope and limits

All **6,301 tracked files** were inventoried and hashed, including **5,387 files under src/**. `configure.py` contains **4,105 distinct literal Object names**; the inventory found no absent configured source paths after resolving both `src/` and `src/static/`. The audit combines whole-tree textual scans and recursive include analysis with manual inspection of build configuration, startup, loader, actor tables, graphics translation, SDK hardware code, audio and the PC architecture. It is not a claim of line-by-line semantic verification of all gameplay logic. No original assets, executable, console, console emulator or devkitxenon compiler were supplied.

`report/compatibility.csv` provides one classification per tracked file, its reason, direct dependency tags, tags through its resolved include graph and SHA-256. Categories are conservative triage: “portable” for three compiler-verified game files and non-runtime artifacts; “requires modification” for gameplay/interfaces/assets/build configuration requiring integration validation; “requires replacement” for GC hardware, debugger, ABI runtime and assembly. These are not estimates of completed port work. Hardware-free source can remain in the modification category because unresolved resources, pointer assumptions or shared headers still need validation. Definitions, comments and included declarations can appear in the textual evidence; a tag alone is not a call-graph finding. Include resolution is heuristic and does not evaluate preprocessor branches.

The classification totals are 61 portable, 6,111 requiring modification and 129 requiring replacement. `report/hardware-evidence.json` records file, line and matched API/address/assembly tokens. `report/unresolved-includes.json` records missing includes, including generated asset headers and SDK/runtime/system include paths; not every entry is a build error. `report/inventory.json` records source/configuration coverage.

## Actual entry and startup sequence

1. `src/static/dolphin/os/__start.c::__start` is the GameCube CRT entry. It initializes registers, r1 stack, r2/r13 SDA bases, hardware, copied sections and BSS; reads boot information at fixed GC addresses; optionally enters MetroTRK; calls `DBInit`, `OSInit`, pad reset checks and `__init_user`, then the DOL's `main`, then `exit`. This assembly startup must be replaced by the Xbox homebrew runtime entry.
2. `src/static/boot.c::main(int,const char**)` is the DOL application entry, not `src/main.c`. It reconfigures BATs, initializes OS/alarm/NMI/reset state and GC arena, calls `JW_Init`, initializes boot audio/menu/DVD error handling, reads `/COPYDATE` and `/static.str`, then loads `/foresta.rel.szs` through `LoadLink`.
3. `boot.c::LoadLink` loads/decompresses through JKR DVD-to-main-RAM, allocates module BSS, registers texture data ranges, calls `OSLink`, then the REL prolog. `UnLink` later calls epilog, removes resource tracking, invokes `OSUnlink` and frees memory.
4. `src/executor.c::_prolog` calls the module `_ctors` unless `construct_skip`, then its `main`. `_epilog` runs `_dtors`; `_unresolved` reports unlinked calls and walks the GC stack.
5. `src/main.c::main(void)` installs `HotStartEntry = &entry`. The DOL loops invoking that pointer. `entry` initializes pad/debug state and calls `mainproc`.
6. `mainproc` sets frame dimensions, card and message queues, IRQ and pad threads and graph thread, starts rendering, completes JW/ARAM/Famicom setup and waits for IRQ messages. `graph.c::graph_proc` drives game state/render lifecycle. An Xbox single-threaded shortcut must preserve queue/timing semantics explicitly; simply stubbing OSCreateThread or OSReceiveMessage would not work.

## Build and binary configuration

`configure.py` supports GAFE01_00 and GAFU01_00. It uses decomp-toolkit extraction, versioned CodeWarrior tools, matching object status and source/data conversion rules. Base flags include Gekko, unsigned char, hardware FP, PowerPC alignment and int enums. REL flags disable sdata/sdata2 and define IS_REL; USA uses GC/1.3.2 and Australia GC/2.6 for foresta. The Xbox target deliberately does not inherit these matching flags or binary extraction link addresses.

`config/*/config.yml`, `symbols.txt` and `splits.txt` describe the original DOL and foresta module, addresses, relocation repairs and extracted resources. `config/GAFE01_00/ldscript.tpl` reserves a GC stack and arena ending at `0x81700000`; it cannot serve as an Xbox linker script. DTK substitutes the template's origin/sections/symbols, which are not a general ELF script.

There are four standalone `.s` files: `JUTFontData_Ascfont_fix12.s` embeds the extracted BFN font with 32-byte alignment; `ctors.s` is a comment-only constructor workaround; MetroTRK `__exception.s` and `targsupp.s` are GC debug/runtime support. The current textual README's claim that there is no assembly is insufficient: extensive CodeWarrior assembly functions and inline instructions also exist in C/C++ headers/sources. Gekko paired-single/quantization, BAT/MSR/cache/exception and GC MMIO assembly must be individually replaced or removed. Standard PowerPC alone does not make those compatible.

## Hardware and interface boundaries

| Area and source anchors | Required handling |
|---|---|
| `static/dolphin/os/{OS.c,OSInterrupt.c,OSContext.c,OSThread.c,OSAlarm.c,OSCache.c}`; `irqmgr.c`; libultra wrappers | Replace exception handlers, scheduler/context switches, interrupt masking, timebase assumptions and cache control. Retain game-facing message/queue/alarm contracts. GC interrupt disable is not a sufficient lock on a multicore target. |
| `static/dolphin/base`, `os/__start.c`, `boot.c::ReconfigBATs`, Dolphin HW headers | Remove GC BAT mappings, low-memory boot/arena globals and address aliases. Pointers cast to u32 require a 32-bit data model. Direct memory access is not made valid by endian compatibility. |
| `static/dolphin/gx/*`, `static/libforest/emu64/emu64.c`, JSystem render/display code, `graph.c`, `PreRender.c` | Keep the existing N64 GBI-to-GX translation where practical; replace GX FIFO/hardware backend with a validated Xenos implementation. GX state, TEV, texture tiling/formats, TLUTs, display lists, copy/EFB behavior, synchronization and VI presentation need equivalents. No SDL/OpenGL/D3D availability is assumed on console. |
| `static/dolphin/dvd/{dvd.c,dvdlow.c,dvdfs.c}`, JKR loaders, `game/m_demo.c`, archive/resource code | Retain DVD file/status/callback interfaces while sourcing data from an extracted filesystem or validated disc-image reader. `dvdlow.c` writes `__DIRegs`, passes physical DMA addresses and uses GC interrupts; replace that implementation. Preserve offsets, compressed archive semantics and callback ordering. |
| `static/dolphin/pad/Pad.c`, SI/GBA drivers, `padmgr.c` | Map controller state to existing PAD/button definitions, calibrate stick/deadzone/trigger behavior and support disconnects/rumble. Replace SI transfers and device probing. GBA connectivity is a separate unsupported feature until implemented. |
| `audio.c`, `static/jaudio_NES`, Dolphin AI/AR/DSP drivers | Sequencer/music logic may survive; AI DMA, ARAM transfers, DSP mailbox/IRAM/DRAM loading and DSP microcode do not. `internal/aictrl.c` uses `AIInitDMA`; `dspboot.c::DspBoot` loads `jdsp` and waits for DSP mail; `dspinterface.c` flushes shared buffers. Requires an actual mixing/DSP-emulation strategy and audio-device backend. |
| `game/m_card.c`, Dolphin CARD/EXI, save/RTC code | Replace hardware transactions while preserving save bytes, CRC/checksum, asynchronous state machines and error handling. Audit every serialized structure separately, including bitfields and padding. Keep GC big-endian disk representation. |
| `static/libjsys`, JSystem/JKernel, `jsyswrap.cpp`, `_mem`/arenas | Retain high-level allocation/resource interfaces; replace OS/DVD/ARAM/GX adapters. Alignment and pointer lifetimes remain critical. Shared headers can compile while leaving many unresolved GC calls. |
| Famicom/NES emulation and JAudio NES integration | Audit embedded CPU/audio emulation independently; host game compilation does not establish NES functionality or compatibility. |

Representative direct-address evidence includes GC OS boot state `0x800000F4`, pad/reset state at `0x800030E4`/`0x800030E6`, DI DMA registers in `dvdlow.c`, DSP control registers in `dspboot.c`, and GX CPU/GP FIFO control and overflow interrupt handling in `GXFifo.c`. The full evidence file includes other matches; literal matching is not exhaustive for indirect register references.

## Platform design and implemented boundary

The proposed platform layer sits **behind existing Dolphin/libultra/JKR/Na interfaces**. Gameplay should retain OSMessageQueue/PAD/DVD/GX/Na call signatures where practical. The game-facing compatibility headers must remain independent of SDK headers to avoid collisions with legacy `u32`, `size_t`, `uintptr_t`, libc, and variadic types. Use separate adapter translation units for SDK headers. Do not import the GameCube OSThread/OSContext layout as the Xbox runtime's native context; use side tables or explicit wrapper-owned state when necessary.

Implemented `platform.h`/`platform.c` provide only a project-owned installation contract for time, synchronous file reads and logging, including validation and one-time registration. The backend is copied, and the getter returns null until installed. The ticks callback must supply GC-compatible units for unchanged callers. No game call is wired to this contract yet; asynchronous DVD, input, threads, graphics and audio are design work still pending. No success-returning dummy OS/GX/audio stubs were added. Missing backends must fail visibly instead of pretending initialization completed.

## Endian and ABI findings

Native BE representation is retained; no byte-swap layer was introduced. Verified checks cover 32-bit pointers/long/u32/s32, 64-bit u64, float width/IEEE precision, TwoHeadArena size 16 and tail offset 12/alignment 4, MtxF size 64, Vec3f size 12, Gfx size/alignment 8, Vtx size 16/alignment 8 and tc/cn offsets 8/12, fixed Mtx size 64/alignment 8. Object symbols encode u32 as `12 34 56 78`, 1.0f as `3f 80 00 00`, white RGB5A3 in a u32 as `00 00 ff ff`, and a Gdma bitfield fixture as `12 34 56 78 9a bc de f0`.

Little-endian macro override and actual PPC64 compilation both fail the guards as intended. These checks cover representative shared types, not every save, actor, GX or OS structure. Bitfield order, enum size, padding, variadic ABI, calling convention, SDA usage, C++ ABI and intrinsic numerical results still need validation with the actual xenon compiler. Float pointer punning in qrand requires `-fno-strict-aliasing`; `-fwrapv` and unsigned-char preserve selected original compiler assumptions without claiming to remove every instance of C undefined behavior.

The inspected libxenon `devkitxenon/rules` uses `xenon-gcc`, **-m32** with `-mpowerpc64`, `-maltivec`, `-fno-pic` and `-mhard-float`. Its `app.lds` enters `_start` and uses Xbox memory ranges. Thus a 64-bit instruction-set capability does not imply a 64-bit game pointer ABI. Our Clang EABI objects are a preliminary representation test and are not asserted to link with libxenon or be console-loadable.

## Static REL feasibility

**Feasible at source level, unproven at full-link/runtime level.** The config lists one extracted module, foresta, not an independent collection of actor RELs. `Rel("actor", ...)` is a compiler/library grouping in configure, not evidence of `actor.rel` in the disc. Actor table `MAKE_ACTOR_DLF` initializes profile addresses directly with zero/null overlay fields. `m_actor.c` obtains `dlftbl->profile`; no binary REL relocation is needed for a source-linked profile table. The table's init sets 246 entries. Actor allocation/free-overlay/data-bank behavior must still be audited before changing lifetime behavior.

Rebuild the foresta/actor/game/effect/furniture/data units into a native static library, resolve imports at final link, rename DOL main and module main at per-source compile boundaries, replace LoadLink/UnLink with an explicit module lifecycle, and adapt constructors/destructors to the native CRT (run each once, preserve construct_skip/hot-start semantics). Remove GC OSLink relocations rather than attempting to reuse GC executable code. Preserve texture-cache range registration/resource ownership when modules are no longer separate allocations. A final map/undefined-symbol audit, extracted assets and memory-budget measurement are required before claiming complete static linkage.

## PC comparison

The inspected PC port supplies `pc_os`, `pc_pad`, `pc_vi`, `pc_dvd`/`pc_disc`, `pc_card`, `pc_aram`, `pc_audio`, GX texture/TEV/render adapters and generated/runtime asset loaders. Its CMake uses SDL2 and OpenGL, enforces 32-bit pointers, applies `-fno-strict-aliasing`/`-fwrapv`, renames game main to `ac_entry` and boot main to `boot_main`, excludes included-only emu64 utility units and compiles selected `.c` files as C++. `pc_main.c` invokes the adapted boot sequence, while TARGET_PC changes replace thread scheduling in game main.

Useful reuse targets are interface boundaries, source lists, asset extraction strategy, symbol renames and scheduling lessons. PC little-endian asset/save byte swapping, GL shader pipeline and SDL device APIs must not be copied blindly to Xbox. This audit did not import PC code or its added gameplay features. The comparison establishes an implementation pattern, not Xbox graphics API support or proof that the PC port's stub coverage is sufficient.

## Compiler and linker results

Compiler: embedded Clang 19.1.7 in Zig 0.14.1 on Windows; target `powerpc-none-eabi`. `zig cc` initially failed before compilation with `unable to find zig self exe path: Unexpected`; `zig clang` worked. The first Clang compilation of all five smoke units failed in `fdlibm.h:234` on undeclared `__fabs` and in `w_math.h:29,62` on undeclared `__frsqrte`. A target-only preinclude maps fabs to the compiler builtin and frsqrte to scalar PowerPC inline assembly. It does not emulate paired-single instructions and has not been numerically tested on Xenon.

Final smoke: all five objects pass, with no compiler diagnostics. Three are unchanged game sources: `static/libc64/qrand.c`, `TwoHeadArena.c`, `system/sys_math_atan.c`; the other two are platform.c and layout.c. Exact commands and diagnostics are in `report/results.json`; ABI/byte checks are in `report/object-checks.json`.

Broader probes successfully compile boot.c, main.c, actor profile table, ac_ant.c, m_card.c, JAudio aictrl.c and jsyswrap.cpp. Compilation does not validate these hardware dependencies. Adding the original include/dolphin search path resolved the initial `m_card.c:3: card.h file not found` problem. Remaining representative failures:

| Probe | Actual compiler blocker |
|---|---|
| executor.c / __start.c | CodeWarrior `__declspec(section ".ctors")` and related section declarations; Clang reports attributes not enabled. Enabling generic declspec would not establish equivalent CodeWarrior syntax/lifecycle. |
| GXFifo.c | undeclared `__sync` (lines 208/238/587) and `PPCMfwpar` (570/615); this GC write-gather hardware path must be replaced. |
| dvd.c | CodeWarrior section syntax plus `asm void __init_hardware` in `os/__os.h`; compilation stops after limited diagnostics. |
| emu64.c, compiled as C++ | CodeWarrior section declarations in shared EABI headers block compilation before deeper graphics/assembly issues. |

The probe uses a five-error limit; these are encountered errors, not an exhaustive compiler-error list. Warnings include VI forward struct visibility, nameless enum typedefs and unused expressions. Raw first/final probe logs are retained under `report/`.

Actual link attempts fail at tool dispatch: explicit `-fuse-ld=lld` reports `invalid linker name`; default reports `unable to execute command: program not executable` and `ld.lld command failed with exit code 1`. No final linker ran to resolve symbols. ELF symbol inspection, separately, finds undefined `bzero` in TwoHeadArena and `sin`/`cos` in sys_math_atan; shared MSL headers also expose undefined `__float_nan` and `__float_huge`. An undefined symbol-table entry does not always imply an active relocation, but these runtime interfaces still need an intentional resolution policy. No stub was added to force a misleading successful link.

## Changes and validation

All changes are additions under xbox360/: object build target, compiler compatibility header, backend contract, layout/byte tests, broader probes, reproducible inventory and reports. Upstream source/build/config files are unchanged (`git diff` against HEAD is empty; xbox360 is untracked). Original `configure.py --help` passes. The original GameCube binary build and hash comparison were not run because no disc image was available.

Successful checks: five smoke objects; actual ELF32/PPC/BE identification; compile-time structure/alignment assertions; four symbol-byte fixtures; two negative ABI guards; broader compile probes listed above; full tracked-file inventory. Failed/unavailable: final linking, console executable packaging, complete game compilation, original binary rebuild and execution on Xbox 360 or a compatible environment. There is no claim that the game runs on Xbox 360.

## Next three concrete tasks

1. Install/pin devkitxenon and libxenon in a reproducible environment; rerun all ABI fixtures with xenon-gcc; integrate the real `_start`/app linker script and CRT; link and run a console test of qrand, arena allocation and time/file/log adapters. Capture serial output and symbol map before expanding the game target.
2. Generate a static foresta source/resource manifest from the config and the user's disc extraction; implement per-source entry renames and native constructor/module lifecycle; produce a full undefined-symbol map and memory budget with GC SDK objects excluded. Implement OS queues/timers/scheduling, filesystem/DVD and controller adapters needed to reach a deterministic headless game tick.
3. Implement one validated Xenos render path for the existing GX interface, starting with clear/present, a textured triangle, tiled texture decode and a representative TEV stage. Compare outputs to GameCube reference captures. In parallel within this milestone, specify the DSP/ARAM replacement and verify a basic PCM audio path before attempting game audio startup.
