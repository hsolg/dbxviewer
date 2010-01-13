# Microsoft Developer Studio Project File - Name="dbxViewer" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=dbxViewer - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "dbxViewer.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "dbxViewer.mak" CFG="dbxViewer - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "dbxViewer - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "dbxViewer - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "dbxViewer - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "dist\Release"
# PROP Intermediate_Dir "build\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "res" /I "src\oedbx" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x414 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x414 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "dbxViewer - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "dist\Debug"
# PROP Intermediate_Dir "build\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "res" /I "src\oedbx" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x414 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x414 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "dbxViewer - Win32 Release"
# Name "dbxViewer - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "oedbx source"

# PROP Default_Filter "cpp"
# Begin Source File

SOURCE=.\src\oedbx\dbxCommon.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\dbxConditions.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\dbxFileHeader.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\dbxFileInfo.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\dbxFolderInfo.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\dbxFolderList.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\dbxIndexedInfo.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\dbxMessage.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\dbxMessageInfo.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\dbxTree.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\gui\DbxUtil.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\gui\dbxViewer.cpp
# End Source File
# Begin Source File

SOURCE=.\res\dbxViewer.rc
# End Source File
# Begin Source File

SOURCE=.\src\gui\dbxViewerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\gui\EmailMessage.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\gui\MessagePart.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\src\gui\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "oedbx headers"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=.\src\oedbx\oedbx\dbxCommon.h
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\oedbx\dbxConditions.h
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\oedbx\dbxFileHeader.h
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\oedbx\dbxFileInfo.h
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\oedbx\dbxFolderInfo.h
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\oedbx\dbxFolderList.h
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\oedbx\dbxIndexedInfo.h
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\oedbx\dbxMessage.h
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\oedbx\dbxMessageInfo.h
# End Source File
# Begin Source File

SOURCE=.\src\oedbx\oedbx\dbxTree.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\gui\DbxUtil.h
# End Source File
# Begin Source File

SOURCE=.\src\gui\dbxViewer.h
# End Source File
# Begin Source File

SOURCE=.\src\gui\dbxViewerDlg.h
# End Source File
# Begin Source File

SOURCE=.\src\gui\EmailMessage.h
# End Source File
# Begin Source File

SOURCE=.\src\gui\MessagePart.h
# End Source File
# Begin Source File

SOURCE=.\res\Resource.h
# End Source File
# Begin Source File

SOURCE=.\src\gui\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\dbxViewer.ico
# End Source File
# Begin Source File

SOURCE=.\res\dbxViewer.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
