# Building Ardour for Windows

These notes document the native MSVC build used for this project. The tested environment was Windows 11 x64, Visual Studio 2026 with the C++ workload, MSVC 14.52, Windows SDK 10.0.26100, Python 3, xmake 3.1.2, and LLVM 22.1.8 (`llvm-nm`).

The official [Ardour MSVC build guide](https://ardour.org/building_msvc.html) describes the upstream build. This repository includes the xmake dependency recipe at `build-support/stack-msvc/xmake.lua` and the Windows installer sources under `installer/`.

## 1. Prepare the tools

Install Visual Studio with the Desktop development with C++ workload and a Windows SDK. Install Python 3, Git, xmake, LLVM (including `llvm-nm`), and Inno Setup 7. Use an x64 Visual Studio Developer PowerShell or Developer Command Prompt so the MSVC compiler, linker, SDK headers, and libraries are available.

Clone the full repository history. A shallow clone or GitHub-generated source ZIP does not provide the Git version data Ardour expects.

## 2. Build the dependency stack

From the repository root, build the dependencies declared in `build-support/stack-msvc/xmake.lua`:

```powershell
Push-Location build-support\stack-msvc
xmake f -c -p windows -a x64 -m release
xmake -j 8
xmake run collect_deps
Pop-Location
```

The recipe stages the dependency headers, libraries, and Windows DLLs in `build-support/stack-msvc/release`.

## 3. Configure and build Ardour

Run these commands from the repository root in the same x64 developer shell:

```powershell
$stack = (Resolve-Path .\build-support\stack-msvc\release).Path
$install = Join-Path (Get-Location) '.build-tools\ardour-install'
$env:PATH = "$stack\bin;$env:PATH"
$env:PKG_CONFIG_PATH = "$stack\lib\pkgconfig"
$env:PKG_CONFIG = "$stack\bin\pkg-config.exe"

python waf configure --prefix="$install" --configdir=share --ptformat --dist-target=msvc --cxx17 --optimize --also-include="$stack\include" --also-libdir="$stack\lib"
python waf -j 8
python waf install -j 8
```

The Windows-specific build fixes for MSVC object-file naming and key-binding script paths are included in this repository.

## 4. Build the GUI launcher

The launcher configures Ardour's runtime paths and starts the main application without a console window. From an x64 developer shell, compile it into the package staging folder:

```powershell
New-Item -ItemType Directory -Force .build-tools\package-root | Out-Null
cl /nologo /O2 /MT /DUNICODE /D_UNICODE /EHsc /std:c++17 /W4 /Fe:.build-tools\package-root\ArdourLauncher.exe installer\ArdourLauncher.cpp /link /SUBSYSTEM:WINDOWS user32.lib
Copy-Item installer\Credits.txt,installer\License-and-Attribution.txt,installer\644684.ico -Destination .build-tools\package-root -Force
```

## 5. Compile the installer

Install Inno Setup 7 and ensure the `VCRedist` path near the top of `installer/Ardour-Windows.iss` points to the x64 Microsoft Visual C++ redistributable from the installed Visual Studio version. Then run:

```powershell
& 'C:\Program Files\Inno Setup 7\ISCC.exe' installer\Ardour-Windows.iss
```

The installer script expects the Ardour installation at `.build-tools/ardour-install` and the launcher and attribution files at `.build-tools/package-root`. The output is written to `.build-tools/installer-output/`.

## Release checks

Before publishing a new installer, verify that the launcher starts Ardour from the staged installation, the version dialog or `--version` output matches the intended source revision, the installer compiles successfully, and its included license and icon files match the release sources.
