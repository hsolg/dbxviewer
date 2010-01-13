Name "dbxViewer"

OutFile "dbxViewer.exe"

InstallDir $PROGRAMFILES\dbxViewer

InstallDirRegKey HKLM "Software\dbxViewer" "Install_Dir"

RequestExecutionLevel admin

; Pages

Page components
Page directory
Page instfiles

;UninstPage uninstConfirm
;UninstPage instfiles

Section "Executable (required)"
  SectionIn RO

  SetOutPath $INSTDIR

  File "..\dist\Release\dbxViewer.exe"
  File "..\LICENSE.txt"

  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\dbxViewer "Install_Dir" "$INSTDIR"


  ;; Write the uninstall keys for Windows
  ;WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Example2" "DisplayName" "NSIS Example2"
  ;WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Example2" "UninstallString" '"$INSTDIR\uninstall.exe"'
  ;WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Example2" "NoModify" 1
  ;WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Example2" "NoRepair" 1
  ;WriteUninstaller "uninstall.exe"
SectionEnd

Section "Start Menu Shortcuts"
  CreateDirectory "$SMPROGRAMS\dbxViewer"
  CreateShortCut "$SMPROGRAMS\dbxViewer\dbxViewer.lnk" "$INSTDIR\dbxViewer.exe" "" "$INSTDIR\dbxViewer.exe" 0
  CreateShortCut "$SMPROGRAMS\dbxViewer\License.lnk" "$INSTDIR\LICENSE.txt" "" "$INSTDIR\LICENSE.txt" 0
  ;CreateShortCut "$SMPROGRAMS\dbxViewer\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
SectionEnd
