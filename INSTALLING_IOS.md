# Installing Nookery on iOS

Nookery isn't on the App Store, so it's installed with [iloader](https://iloader.app/),
which signs the app with your own Apple ID.

## Prerequisites

- A Windows, Linux, or macOS computer
- Your iPhone or iPad, connected to the computer via USB
- The Nookery `.ipa` from the [Releases](https://github.com/flyngmt/ACGC-PC-Port/releases) page
- A legally obtained GAFE01 Rev 0 (USA) disc image (RVZ, ISO, CISO or GCM)

## 1. Install iloader

Download iloader from [iloader.app](https://iloader.app/) or
[its GitHub](https://github.com/nab138/iloader/releases). Don't download it from anywhere else.

- On Windows, you'll also need [iTunes](https://apple.co/ms).
- On Linux, you'll need `usbmuxd`. Most distros already have it.

## 2. Enable Developer Mode (iOS 16+)

On your device, go to **Settings > Privacy & Security > Developer Mode**, turn it on,
enter your passcode, and restart when asked.

## 3. Install Nookery

1. Open iloader and sign in with your Apple ID. It's only sent to Apple to register the app.
   If you have two-factor authentication on, enter the code from your device.
2. Plug in your device and press **Refresh** so iloader finds it.
3. Leave the settings as they are.
4. Press **Import IPA** and pick the Nookery `.ipa`. It'll install on your device.

Tap **Trust** on your device whenever it asks you to trust the computer.

## 4. Trust the app

The first time, iOS won't open the app until you trust it:

1. Go to **Settings > General > VPN & Device Management**.
2. Under **Developer App**, tap the Apple ID you used in iloader, then tap **Trust**.
3. Tap **Allow**.

## 5. Copy your files

Copy your disc image to your device so it shows up in the Files app, using AirDrop,
iCloud Drive, a USB transfer through Finder or iTunes, or any cloud storage app.
Then open Nookery and select it.

For the texture pack, download the PNG version and copy it into the `texture_pack`
folder under **On My iPhone (or iPad) > Nookery** in the Files app.
