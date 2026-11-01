#!/bin/bash -ex

if [[ -n "${GITHUB_WORKSPACE:-}" ]]; then
  cd "$GITHUB_WORKSPACE"
fi

cd build/install
arch="$(lipo -archs Nookery.app/Contents/MacOS/Nookery | tr ' ' '-')"
ditto -c -k --norsrc --noextattr --noacl --keepParent Nookery.app "Nookery-${APP_VERSION}-macos-${arch}.zip"
