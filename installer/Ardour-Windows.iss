#define AppVersion "9.10.16"
#define AppName "Ardour 9"
#define BuildDir "..\.build-tools\ardour-install"
#define PackageDir "..\.build-tools\package-root"
#define OutputDir "..\.build-tools\installer-output"
#define VCRedist "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Redist\MSVC\14.52.37025\vc_redist.x64.exe"

[Setup]
AppId={{9F2414BD-86D9-4F53-A8E8-AD0097A16401}
AppName={#AppName}
AppVersion={#AppVersion}
AppVerName={#AppName} {#AppVersion} (Windows build by Ivan-Ayub97)
AppPublisher=Ivan-Ayub97
AppComments=Native Windows build of Ardour
AppReadmeFile={app}\Credits.txt
DefaultDirName={autopf}\Ardour 9
DefaultGroupName=Ardour 9
UninstallDisplayIcon={app}\lib\ardour9\ardour-9.10.16.exe
OutputDir={#OutputDir}
OutputBaseFilename=Ardour-9.10.16-Winx64-Ivan-Ayub97-Setup
ArchitecturesAllowed=x64
ArchitecturesInstallIn64BitMode=x64
PrivilegesRequired=admin
Compression=lzma2/ultra64
SolidCompression=yes
WizardStyle=modern
SetupIconFile=644684.ico
UninstallIconFile=644684.ico
WizardImageFile=644684-wizard.png
WizardSmallImageFile=644684.png
InfoBeforeFile={#PackageDir}\Credits.txt
LicenseFile={#PackageDir}\License-and-Attribution.txt
SetupLogging=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "Create a desktop shortcut"; Flags: unchecked

[Files]
Source: "{#BuildDir}\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "{#PackageDir}\ArdourLauncher.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#PackageDir}\Credits.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#PackageDir}\License-and-Attribution.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "644684.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "..\COPYING"; DestDir: "{app}"; Flags: ignoreversion
Source: "{#VCRedist}"; DestDir: "{tmp}"; Flags: deleteafterinstall

[Icons]
Name: "{group}\Ardour 9"; Filename: "{app}\ArdourLauncher.exe"; WorkingDir: "{app}"; IconFilename: "{app}\644684.ico"
Name: "{autodesktop}\Ardour 9"; Filename: "{app}\ArdourLauncher.exe"; WorkingDir: "{app}"; IconFilename: "{app}\644684.ico"; Tasks: desktopicon

[Run]
Filename: "{tmp}\vc_redist.x64.exe"; Parameters: "/install /quiet /norestart"; StatusMsg: "Installing the Microsoft Visual C++ runtime..."; Flags: waituntilterminated; Check: not IsRuntimeInstalled

[Code]
function IsRuntimeInstalled: Boolean;
var
  Installed: Cardinal;
begin
  Result := RegQueryDWordValue(HKLM64,
    'SOFTWARE\Microsoft\VisualStudio\14.0\VC\Runtimes\X64', 'Installed', Installed) and (Installed = 1);
end;
