# Source from bash:  source xbox/toolchain/xenon_env.sh
# Uses an existing $DEVKITXENON if set; otherwise build/xbox/devkitxenon in this repo.
# (Codex's earlier install lives at <ac-decomp>/build/xbox360/devkitxenon; you can
#  point DEVKITXENON there instead of rebuilding.)
ac_xbox_repo=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/../.." && pwd)
export DEVKITXENON="${DEVKITXENON:-$ac_xbox_repo/build/xbox/devkitxenon}"
export PATH="$DEVKITXENON/bin:$DEVKITXENON/usr/bin:$PATH"
unset ac_xbox_repo
