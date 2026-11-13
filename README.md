<div align="center">
  <img src="installer/644684.png" alt="Ardour Windows build artwork" width="180">

  # Ardour 9 for Windows

  **An independent, native x64 Windows build of Ardour, compiled with Microsoft Visual C++.**

  [Download the latest installer](https://github.com/Ivan-Ayub97/Ardour9-WinBuild/releases/latest) ·
  [Build instructions](BUILDING.md) ·
  [License](COPYING)
</div>

---

## Overview

This repository contains the Ardour source tree and the Windows-specific build and packaging work used to produce the **Ardour 9.10.16** installer. The release was compiled natively for 64-bit Windows with MSVC from upstream revision `9.10-16-g1661b06c0d`.

This is an independent community build. It is not an official Ardour release and is not endorsed by the Ardour project.

## Download and install

Download **`Ardour-9.10.16-Winx64-Ivan-Ayub97-Setup.exe`** from [GitHub Releases](https://github.com/Ivan-Ayub97/Ardour9-WinBuild/releases/latest), run it, and follow the English setup wizard. The installer creates a Start Menu shortcut and can optionally create a desktop shortcut using the project artwork.

The installer bundles the application files, its runtime libraries, and the Microsoft Visual C++ runtime installer. The build tools used to compile Ardour are not required on the target computer.

## Features

- Native 64-bit Windows executable built with MSVC.
- Ardour's audio and MIDI editing, mixing, automation, and included plug-ins from this source build.
- Bundled application resources and runtime DLLs.
- A Windows GUI launcher that configures Ardour's resource paths without opening a Command Prompt window.
- English-language Inno Setup installer with the full Ardour license text and attribution.

## System requirements

- 64-bit Windows 10 or later is recommended. This build has been produced and smoke-checked on Windows 11 x64.
- At least 200 MB of free disk space for installation; recording sessions require additional storage.
- A supported audio device and its Windows driver. For low-latency recording, install the device manufacturer's ASIO driver. ASIO4ALL or Windows audio drivers may be alternatives depending on the device.
- Internet access is only needed to download the installer; the build toolchain is not needed to install or run Ardour.

## Known limitations

- The video helper applications distributed with the official Windows package (Harvid, FFmpeg, and XJadeo) are not bundled in this build. Video playback and video-monitor workflows may therefore be unavailable.
- Some optional USB control-surface integrations were not enabled in this build.
- Audio interface drivers and third-party plug-ins are not included; install them separately from their respective vendors.
- The installer is not digitally signed. Windows SmartScreen may show a download warning.

## Build from source

See [BUILDING.md](BUILDING.md) for the tested MSVC toolchain, dependency-stack recipe, Ardour build steps, launcher compilation, and installer packaging instructions. A full Git checkout is required because Ardour derives version information from Git history.

The upstream project is [Ardour](https://github.com/Ardour/ardour). This repository retains its upstream history and includes the build changes and Windows packaging files used for this distribution.

## License and credits

Ardour is licensed under the **GNU General Public License, version 2 or (at your option) any later version**. The complete original license and Ardour's plugin clarification are in [COPYING](COPYING). Individual third-party components retain their own notices and licenses in the source tree.

Windows compilation, build support changes, launcher, and installer packaging prepared by **Ivan-Ayub97**. Ardour and the names and marks of its contributors remain theirs; this project does not claim authorship of Ardour or its third-party components.
