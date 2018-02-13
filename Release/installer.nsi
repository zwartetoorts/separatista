Name "Separatista installer"
OutFile "Separatista.exe"

InstallDir "$PROGRAMFILES\Separatista"
InstallDirRegKey HKCU "Software\Separatista\Separatista" Path

LicenseBkColor /windows
LicenseData "gpl-3.0.txt"
LicenseForceSelection checkbox "I accept the license"

Page License
Page Directory
Page instFiles

UninstPage uninstConfirm
UninstPage instFiles

Section "SeparatistaLib"
  SetOutPath "$INSTDIR"
  File "SeparatistaIBAN.dll"
  File "MT940S.dll"
  File "Separatista.dll"
  WriteRegStr HKCU "Software\Separatista\Separatista" Path "$INSTDIR"
SectionEnd

Section "ClieopControl"
  SetOutPath "$INSTDIR"
  File "SeparatistaControl.dll"
  RegDll "$INSTDIR\SeparatistaControl.dll"
SectionEnd

Section "SeparatistaGUI"
   SetOutPath "$INSTDIR"
   File "SeparatistaGUI.exe"
   File "..\win32\SeparatistaGUI\urn_iso_std_iso_20022_tech_xsd_pain.008.001.02.txt"
SectionEnd

Section "Cleanup"
  WriteUninstaller "uninstall.exe"
SectionEnd

Section "Shortcuts"
  CreateDirectory "$SMPROGRAMS\Separatista"
  CreateShortCut "$SMPROGRAMS\Separatista\Separatista Editor.lnk" "$INSTDIR\SeparatistaGUI.exe"
  CreateShortCut "$SMPROGRAMS\Separatista\Website Separatista.lnk" "http://separatista.eu"
  CreateShortCut "$SMPROGRAMS\Separatista\Uninstall.lnk" "$INSTDIR\uninstall.exe"
SectionEnd

Section "uninstall"
  UnRegDll "$INSTDIR\SeparatistaControl.dll"
  
  Delete "$INSTDIR\SeparatistaGUI.exe"
  Delete "$INSTDIR\urn_iso_std_iso_20022_tech_xsd_pain.008.001.02.txt"
  Delete "$INSTDIR\SeparatistaControl.dll"
  Delete "$INSTDIR\Separatista.dll"
  Delete "$INSTDIR\MT940S.dll"
  Delete "$INSTDIR\SeparatistaIBAN.dll"
  
  Delete "$SMPROGRAMS\Separatista\*.*"
  
  RMDir /r "$SMPROGRAMS\Separatista"
  RMDir /r "$INSTDIR"
SectionEnd