# Pinned Ubuntu Xenon build

> Copied from the Codex prototype (`xbox360/TOOLCHAIN.md`). Paths there refer to the old
> `ac-decomp/xbox360/` layout; in this repo the files are under `xbox/toolchain/` and the
> default install location is `build/xbox/devkitxenon`.

The installed toolchain is retained locally at `build/xbox360/devkitxenon` (ignored build output). In bash:

```sh
source xbox360/xenon_env.sh
xenon-gcc --version
```

The source build was installed first at `/tmp/ac-devkitxenon`, then copied to the repository. The relocated compiler and its PPC32 libgcc path were checked. This does not modify shell startup files or the GameCube build. New evidence is under `xbox360/report/xenon`; previous Windows reports and archive remain separate.

## Sources and dependency review

`toolchain-lock.json` pins libxenon commit `c32c813c3d630ae922f83395ee4509b0468af71d`, GCC 9.2.0, binutils 2.32 and newlib 3.1.0, including archive and patch SHA-256 values. These are locally captured HTTPS download hashes, not independent publisher-signature verification.

All four inspected source URLs returned HTTP 200, including the upstream recipe's GCC 16.2.0 mirror URL. GCC 9.2.0 was selected with the matching patch already present in the pinned SDK. That patch accepts the Xenon target and disables AltiVec operations unsupported by Xenon. All three selected patches applied with `--fuzz=0` and all selected archives passed the recorded hashes.

The upstream script was read but **not executed**. Its automatic sudo package installation, broad cleanup/chown, `/opt/local` host-library paths, optional library downloads and moving filesystem Git checkouts are absent from our recipe. Only the compiler, runtime and libxenon needed for these checks are installed. Optional zlib/libpng/freetype/filesystem libraries are not claimed to be installed.

The initially missing dependencies were installed by the user after `sudo -n apt-get update` failed with `sudo: interactive authentication is required`:

```sh
sudo apt-get update
sudo apt-get install -y build-essential flex bison libgmp-dev libmpfr-dev libmpc-dev texinfo zlib1g-dev
```

Exact installed package versions are in `report/xenon/environment.json`. GCC 15.2.0 is the host compiler; GCC 9.2.0 is the cross compiler. Host compilation uses `-std=gnu++11` and `-fcommon` to build these older sources; newlib target flags also include `-fcommon`. The final cross compiler has C/C++ and 32/64-bit multilibs. Game compilation explicitly selects `-m32`; 64-bit instruction support is not a 64-bit pointer ABI.

## Rebuild the installation

Use a Linux filesystem for sources/builds to avoid slow cross-filesystem access. Download the three locked URLs to `/tmp/ac-xenon-downloads`, then:

```sh
git clone https://github.com/Free60Project/libxenon.git /tmp/ac-libxenon
git -C /tmp/ac-libxenon checkout c32c813c3d630ae922f83395ee4509b0468af71d
mkdir -p /tmp/ac-xenon-downloads
curl -fL -o /tmp/ac-xenon-downloads/binutils-2.32.tar.xz https://ftp.gnu.org/gnu/binutils/binutils-2.32.tar.xz
curl -fL -o /tmp/ac-xenon-downloads/gcc-9.2.0.tar.xz https://ftp.gnu.org/gnu/gcc/gcc-9.2.0/gcc-9.2.0.tar.xz
curl -fL -o /tmp/ac-xenon-downloads/newlib-3.1.0.tar.gz https://sourceware.org/pub/newlib/newlib-3.1.0.tar.gz
python3 xbox360/install_toolchain.py --sdk /tmp/ac-libxenon --downloads /tmp/ac-xenon-downloads --work /tmp/ac-xenon-build --prefix /tmp/ac-devkitxenon --jobs 6
cp -a /tmp/ac-devkitxenon build/xbox360/devkitxenon
```

Use fresh directories when reproducing a build. The installer supports resuming completed stages with marker files; that is a convenience, not verification of an arbitrary existing installation. It rejects unexpected hashes and partially extracted source directories. Per-stage commands, exit codes and logs are retained in `report/xenon/toolchain/` for the completed build. Source archives/build trees are currently under `/tmp`; fetch/rebuild them again if those temporary directories are removed.

## Native checks

```sh
source xbox360/xenon_env.sh
AC_XENON_FLAGS='-DXENON -m32 -maltivec -fno-pic -mpowerpc64 -mhard-float'
python3 xbox360/build.py --cc xenon-gcc --flags="$AC_XENON_FLAGS" --out-dir build/xbox360/xenon
python3 xbox360/probe.py --cc xenon-gcc --flags="$AC_XENON_FLAGS -fmax-errors=5" --ppc64-flags=-m64 --gcc-linker --out-dir build/xbox360/xenon
python3 xbox360/sdk_probe.py --cc xenon-gcc --flags="$AC_XENON_FLAGS" --libxenon /tmp/ac-libxenon --out-dir build/xbox360/xenon --report-dir xbox360/report/xenon
python3 xbox360/static_target.py --cc xenon-gcc --ar xenon-ar --flags="$AC_XENON_FLAGS -fmax-errors=3 -Werror=return-type -Werror=implicit-int" --out-dir build/xbox360/xenon/static --report-dir xbox360/report/xenon
python3 xbox360/check_archive.py --archive build/xbox360/xenon/static/foresta-partial.a --report-dir xbox360/report/xenon
python3 xbox360/link_probe.py --prefix "$DEVKITXENON" --out-dir build/xbox360/xenon --archive build/xbox360/xenon/static/foresta-partial.a --report-dir xbox360/report/xenon
```

The source sweep records failed units and still archives passing ones. The link probe records individual failures; process completion is not a successful game link. A GCC inline-semantics experiment is also retained in the native reports. It does not fix the legacy math ABI and is not a proposed solution. Game-header emission/linkage needs a reviewed target-only policy rather than a linker option that permits duplicate definitions.

`tests/runtime.c` and `tests/console_main.c` describe future qrand/arena checks; they were compiled, not executed. `tests/sdk_link_main.c` is a separate SDK-only serial-print diagnostic. No asset arrays, hardware stubs, or replacement SDK declarations were added. No console execution, shader output, game initialization, audio or input behavior is verified.
