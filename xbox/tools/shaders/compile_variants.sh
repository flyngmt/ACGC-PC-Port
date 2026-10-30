#!/bin/bash
# Compiles default.frag variants: mkvariants.py -> glslang -> spirv-opt -> xsc.
# Usage: compile_variants.sh <work dir>
# Needs XSDK_DIR (with build/host/libxsc.so built) and glslang, spirv-opt, spirv-dis and spirv-as
# on PATH or named by GLSLANG, SPIRV_OPT, SPIRV_DIS and SPIRV_AS. Tested at xsdk 8c58c7a.
set -e
here=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
repo=$here/../../..
work=$(mkdir -p "$1" && cd "$1" && pwd)
: "${XSDK_DIR:?set XSDK_DIR to an xsdk checkout}"
G=${GLSLANG:-glslang}; O=${SPIRV_OPT:-spirv-opt}; D=${SPIRV_DIS:-spirv-dis}; A=${SPIRV_AS:-spirv-as}

python3 "$here/mkvariants.py" "$repo/pc/shaders/default.frag" "$work/v" > /dev/null

fold="--scalar-replacement=0 --convert-local-access-chains --eliminate-local-single-block
      --eliminate-local-single-store --eliminate-local-multi-store --ccp --simplify-instructions
      --eliminate-dead-branches --merge-blocks --eliminate-dead-code-aggressive"
passes="--merge-return --inline-entry-points-exhaustive --eliminate-dead-functions
        $fold $fold $fold $fold
        --eliminate-dead-inserts --vector-dce --redundancy-elimination $fold"

status=0
for f in "$work"/v/*.frag; do
    n=${f%.frag}
    rm -f "$n.bin"
    "$G" -G --target-env opengl --auto-map-locations --auto-map-bindings "$f" -o "$n.raw.spv" > /dev/null
    "$O" $passes --target-env=opengl4.5 "$n.raw.spv" -o "$n.opt.spv" 2>&1 | grep -v 'could not be inlined' || true
    # xsc has no OpFUnord*; these differ from OpFOrd* only for NaN
    "$D" "$n.opt.spv" | sed -E 's/OpFUnord(LessThanEqual|LessThan|GreaterThanEqual|GreaterThan|Equal|NotEqual)/OpFOrd\1/' > "$n.spvasm"
    "$A" --target-env spv1.0 "$n.spvasm" -o "$n.f.spv"
    if msg=$(cd "$XSDK_DIR/xenos-toolchain" && python3 -m xsc.lower "$n.f.spv" -o "$n.bin" --optimize 2>&1 | tail -1) && [ -s "$n.bin" ]; then
        echo "OK   $(basename "$n") $(stat -c%s "$n.bin") bytes"
    else
        echo "FAIL $(basename "$n"): $msg"
        case $n in *uber) ;; *) status=1 ;; esac
    fi
done
exit $status
