# Presentation diagnostic — 2026-10-14

The user confirmed the real add_calc update diagnostic worked, but reported a
horizontal tear climbing through the moving GC panels. This is console evidence
of the animation working; tear-free presentation remains unverified.

Subsequent console result: the user confirmed no tearing and the final PRESENT
v1 PASS. This verifies the 900-frame diagnostic on their console. It does not
establish presentation behavior for every video mode or full game workload.

The separate game-present-scene target allocates two independent tiled BGRA8888
surfaces with the existing Xe_CreateTexture API. Each frame resolves and
synchronizes the back buffer, waits for a fresh Xe_IsVBlank edge, and selects
that surface with Xe_SetFrameBufferSurface. It waits for blank to end before
continuing. These are verified SDK interfaces; the register-based scanout
switch is not assumed to be an atomic presentation API. Each wait has a 100ms
timeout with a visible error. No original GameCube build changes are required.

The diagnostic retains the external ACSCENE.BIN load, actual game add_calc
function, cooperative scheduler, and 900 update/render acknowledgements. Final
PASS additionally requires 900 buffer switches. Rebinding the console at the
end clears the displayed surface, so a text-only final screen is expected.

```sh
source xbox360/xenon_env.sh
python3 xbox360/startup_probe.py --prefix "$DEVKITXENON" --diagnostic game-present-scene
```

Copy build/xbox360/game-present-scene-testing/xenon.elf and ACSCENE.BIN to the
FAT32 USB root. Observe approximately 30 seconds of moving panels and report
whether the climbing horizontal tear remains. Expected final text begins
PRESENT v1 PASS. Report any timeout caption verbatim.

Python and generated PowerPC C syntax checks passed locally. Native GCC linking,
runtime blank timing, and removal of tearing await Ubuntu build and console
testing. The builder also runs its existing FAT32 and host scheduler checks;
host checks do not establish native presentation behavior.
