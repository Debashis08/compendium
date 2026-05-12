; Script generated for Qt Quick Application
; Located at: packaging/windows/windows-setup.iss

#define MyAppName "compendium"
#define MyAppPublisher "My Company"
#define MyAppExeName "compendium.exe"

; Default value for local testing. In CI, this is overwritten via command line.
; Updated to step back two directories (packaging/windows) to reach the project root
#ifndef MyAppSourceDir
  #define MyAppSourceDir "..\..\build\release"
#endif

#ifndef MyAppVersion
  #define MyAppVersion "1.0.0"
#endif

#ifndef MyOutputFilename
  #define MyOutputFilename "MyPOC_Setup"
#endif

[Setup]
AppId={{A1B2C3D4-E5F6-7890-1234-2c0m2p6d05}}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppPublisher={#MyAppPublisher}

; --- CRITICAL CHANGE FOR LOGGING ---
; Installs to C:\Users\<Name>\AppData\Local\compendium
DefaultDirName={localappdata}\{#MyAppName}

; Ensure we don't ask for Admin password (since we are installing to user folder)
PrivilegesRequired=lowest
; -----------------------------------

DefaultGroupName={#MyAppName}

; Output configuration
; You can also change this to "..\..\Output" if you want the installer built at the project root
OutputDir=Output
OutputBaseFilename={#MyOutputFilename}
Compression=lzma
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64compatible

; UPDATE FLOW SETTINGS
CloseApplications=yes
RestartApplications=no

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
; The main executable
Source: "{#MyAppSourceDir}\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion

; All other files (DLLs, plugins, qml folders) recursively
Source: "{#MyAppSourceDir}\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#MyAppName}}"; Flags: nowait postinstall skipifsilent