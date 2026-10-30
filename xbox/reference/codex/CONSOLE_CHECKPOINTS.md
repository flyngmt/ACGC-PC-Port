# Deferred console checkpoints

Work continues with local checks without waiting for a console run, per the
user's instruction on 2026-10-20. These are optional checkpoints to return to;
pending hardware results are not treated as verified.

| Checkpoint | Status | Evidence |
| --- | --- | --- |
| actor-batch | User-confirmed PASS | 3/3 ctor/dtor, 900/900 move/draw, 6 opens, 12 captured sound requests |
| actor-model-batch | User-confirmed PASS | Correct final values, including 2,700 model dispatches |
| scene-actor-batch | Locally compiled and host-tested; covered by newest batch | Shared original actor lists and per-scene cache lifetime |
| scene-walk-batch | Locally compiled and host-tested; covered by newest batch | Cumulative ownership, cache, callback traversal and deferred retirement checks |
| resident-scene-batch | Milestone locally complete; deferred console run | Cumulative checks plus all actors prepared before every update |

## Scene ownership checkpoint

Run these later from the repository in Ubuntu WSL:

```sh
source xbox360/xenon_env.sh
python3 xbox360/startup_probe.py --prefix "$DEVKITXENON" --diagnostic scene-actor-batch
```

Copy `xenon.elf`, `ACDVD.BIN`, and `ACTRAIN.BIN` from
`build/xbox360/scene-actor-batch-testing/` to the FAT32 USB root and launch via XeLL.
The asset files are unchanged from the verified model-dispatch checkpoint.

One launch runs all six stages. Check:

1. Moving panels and train openings remain smooth; glass behaves as before.
2. All six stage results pass and the final label is `SCENE OWNERSHIP v1 PASS`.
3. Shared lists report **6 attaches/6 detaches**.
4. Cache reports **9 decodes/2691 hits**, with **2700 dispatches**.
5. Actor totals remain **3/3**, **900/900**, **6 opens**, **12 captured SFX**.
6. Final ownership/heap checks pass, and the screen holds without rebooting.

If it fails, record the stage and error line. No sound is expected: original
door SFX remain capture-only. This checkpoint does not test full spawning,
collision, NPC/field behavior, saves, XEX startup or wireless controllers.

[Implementation and local test evidence](SCENE_ACTOR_OWNERSHIP.md)

## Newest cumulative checkpoint: scene traversal

The newest batch includes all scene-actor-batch checks; you do not need to run
both pending checkpoints. Build later in Ubuntu WSL:

```sh
source xbox360/xenon_env.sh
python3 xbox360/startup_probe.py --prefix "$DEVKITXENON" --diagnostic scene-walk-batch
```

Use `xenon.elf`, `ACDVD.BIN`, `ACTRAIN.BIN` from
`build/xbox360/scene-walk-batch-testing/`. Assets retain their existing bytes.

Expected final screen: **SCENE TRAVERSAL v1 PASS**, with:

- 1,803 walks, 3,599 visits, 3 deferred retirements.
- Dummy move/draw callbacks 898/898 (construction timing is explained in the report).
- Existing ownership 6/6, cache 9 decodes/2,691 hits, and 2,700 model dispatches.
- Existing actor totals 3/3, 900/900, 6 opens, 12 captured SFX.

Visuals should remain the same as the earlier batch: smooth panels/train and
normal-depth glass visible behind the frame. No audio is expected. Final screen
holds; no automatic reboot. Hardware confirmation remains deferred and does not
block work.

[Traversal implementation and local evidence](SCENE_ACTOR_TRAVERSAL.md)

## Current milestone checkpoint: resident scene preparation

Use **resident-scene-batch** for the next console session. It includes all
pending ownership/traversal checks, so no extra launches are needed:

```sh
source xbox360/xenon_env.sh
python3 xbox360/startup_probe.py --prefix "$DEVKITXENON" --diagnostic resident-scene-batch
```

Files: `xenon.elf`, `ACDVD.BIN`, `ACTRAIN.BIN` in
`build/xbox360/resident-scene-batch-testing/`.

Expected: **RESIDENT SCENE v1 PASS**, readiness/commits **900/900**, walks/visits
**1803/3603**, deferred retirements **3**, Dummy callbacks **900/900**, ownership
**6/6**, cache **9/2691**, dispatches **2700**, train **3/3**, **900/900**, opens
**6**, captured SFX **12**. Visuals should remain smooth with glass behind the
frame. Hardware verification is deferred; implementation/local validation is
complete and development can proceed.

[Milestone report and evidence](RESIDENT_SCENE_MILESTONE.md)

## Original boot-logo draw slice (separate startup check)

Major milestone 3 is now the active focus. The `boot-logo` target uses the real
original logo emitter and original bootdata; it does not execute full boot/menu
initialization. This is not a substitute for completing milestone 3.

```sh
source xbox360/xenon_env.sh
python3 xbox360/startup_probe.py --prefix "$DEVKITXENON" --diagnostic boot-logo
```

Copy only `build/xbox360/boot-logo-testing/xenon.elf`. Expect a static red Nintendo
logo on black and a hold without reboot; no audio, fade or game transition.
No external asset files are required. Hardware verification remains deferred.
Do not launch the host runner's `boot-emitter-link-check.elf` (link check only).

[Startup path, implementation and remaining blockers](ORIGINAL_STARTUP_SCREEN.md)

## Menu lifecycle development status

The actual original menu init/worker/cleanup passed controlled host execution
(336 simulated frames) and allocation failure tests. No new native full-menu
checkpoint is published: production heap/thread/display bindings remain pending,
and the test backend is not used by console builds. Existing boot-logo and
resident-scene checks stay deferred; no new console run is required to continue.

[Host evidence and remaining bindings](BOOT_MENU_LIFECYCLE.md)

Boot production services: PPC object compilation and prior controlled menu regressions pass. No new console ELF to test yet. Linux scheduler/thread retirement tests are available via test_boot_services.py --host-cc cc; native integration and console execution remain deferred.

2026-10-29 Aurora CPU texture slice: host vectors, existing train pixels and PPC compilation pass. No additional console reboot requested. Next cumulative train build should retain door/glass appearance; new CMPR/RGBA8 native upload/alpha/sampling checks remain deferred until their loader dispatch is connected.

2026-10-29: optional timg-texture target (six static RGBA8/CMPR alpha/filter stages, one launch, embedded synthetic ResTIMG resources). Parser/mip/channel/recorded SDK contract tests and generated source PPC compilation pass. GNU final link and GPU execution pending. End text is '6/6 stages submitted', NOT visual accuracy PASS. See TIMG_RESOURCE_UPLOAD.md for expected panels. Storage and GPU mip sampling are not tested by this target.

2026-10-30: train CI4/I8 decoding now uses the shared eleven-format decoder; saved pixels and resident/actor/cache host checks pass. No additional reboot requested. Confirm unchanged door/glass appearance on the next cumulative train build. Indexed/intensity formats have CPU and recorded-upload checks, not new GPU confirmations. See GX_COMMON_TEXTURES.md.

2026-10-30: gx-texture-owned supersedes timg-texture for the next optional texture-specific console launch. Same six visual stages, now via actual GX signatures, owned spans, native cache and Xe_Sync fence, followed by checked owner release. New code and generated main compile for PPC; 27 fresh host test runs pass. No GNU final link/GPU run here. No additional console test blocks development. See GX_TEXTURE_OWNERSHIP.md.
