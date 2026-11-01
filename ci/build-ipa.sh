#!/bin/bash -ex

if [[ -n "${GITHUB_WORKSPACE:-}" ]]; then
  cd "$GITHUB_WORKSPACE"
fi

cd build/install
rm -rf Payload
mkdir Payload
cp -R Nookery.app Payload/
zip -qry "Nookery-${APP_VERSION}-ios-arm64.ipa" Payload
rm -rf Payload
