# Xenos shader pipeline

Compiles `pc/shaders/default.frag` variants for Xenos with no XDK output:
GLSL → `glslang` → `spirv-opt` → `xsc` (from [xsdk](https://github.com/xenosworks/xsdk), tested at `8c58c7a`) → libxenon shader container.
The variants here are hand-picked test cases, not the game's real set. The unmodified ubershader is refused by `xsc`; `compile_variants.sh` expects that.

```sh
export XSDK_DIR=/path/to/xsdk          # after: make -C "$XSDK_DIR" build/host/libxsc.so
xbox/tools/shaders/compile_variants.sh build/xbox/shader-test
python3 xbox/tools/shaders/simtest.py build/xbox/shader-test
python3 xbox/tools/shaders/gen_smoke_header.py build/xbox/shader-test xbox/tests/shader_smoke/smoke_shaders.h
```

- `mkvariants.py` mirrors `pc_gx_tev.c`'s const block, expands the fixed loops, moves the remaining uniforms into a `std140` block and stores the output once.
- `simtest.py` runs each variant on `xsc`'s simulator against a Python TEV reference. Always run it: `xsc` silently dropped fog when `fragColor` was stored whole and then rewritten by component.
- `gen_smoke_header.py` compiles `smoke.vert` and embeds the shaders for `xbox/tests/shader_smoke`.

`--optimize` is required: without it the 8-light variant needs 18 registers, over libxenon's 16.
