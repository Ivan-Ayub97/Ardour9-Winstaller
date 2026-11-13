# Ardour 9.10.16 — Windows x64

First Windows x64 installer release for this independent MSVC build.

## Included

- Native Ardour build from upstream revision `9.10-16-g1661b06c0d`.
- Bundled application resources and runtime libraries.
- GUI launcher, English Inno Setup wizard, full Ardour license text, and custom installer and shortcut artwork.
- Microsoft Visual C++ runtime installer, applied when the runtime is not already present.

## Known limitations

- Harvid, FFmpeg, and XJadeo video helper applications are not included.
- Some optional USB control-surface integrations were not enabled.
- The installer is unsigned; Windows may show a SmartScreen warning.

See [README.md](README.md) for system requirements, installation guidance, and license information.
