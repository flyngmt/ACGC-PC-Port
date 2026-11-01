#!/bin/bash -ex

if [[ -n "${GITHUB_WORKSPACE:-}" ]]; then
  cd "$GITHUB_WORKSPACE"
fi

build_dir="$PWD/build"
linuxdeploy="$build_dir/linuxdeploy-$(uname -m).AppImage"
lib_dir="/usr/lib/$(uname -m)-linux-gnu"

# Get linuxdeploy
mkdir -p "$build_dir"
curl -fL "https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-$(uname -m).AppImage" -o "$linuxdeploy"
chmod +x "$linuxdeploy"

# Build AppImage
rm -rf build/appdir
mkdir -p build/appdir/usr/{bin,share/{applications,icons/hicolor}}
for install_path in build/install/*; do
  # Skip debug files and archives
  [[ "$(basename "$install_path")" == *.* ]] && continue
  cp -r "$install_path" build/appdir/usr/bin
done
cp -r platforms/freedesktop/{16x16,32x32,48x48,64x64,128x128,256x256} build/appdir/usr/share/icons/hicolor
cp platforms/freedesktop/com.flyngmt.nookery.desktop build/appdir/usr/share/applications

# SDL loads libusb at runtime, so linuxdeploy can't discover it
cd build/install
VERSION="$APP_VERSION" NO_STRIP=1 "$linuxdeploy" \
  -l "$lib_dir/libusb-1.0.so" --appdir "$build_dir/appdir" --output appimage
