# Microsoft Visual C++ Generated NMAKE File, Format Version 2.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

!IF "$(CFG)" == ""
CFG=Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Win32 Release" && "$(CFG)" != "Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "MDATHUNK.MAK" CFG="Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

################################################################################
# Begin Project
# PROP Target_Last_Scanned "Win32 Debug"
MTL=MkTypLib.exe
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "WinRel"
# PROP Intermediate_Dir "WinRel"
OUTDIR=.\WinRel
INTDIR=.\WinRel

ALL : $(OUTDIR)/MDATHUNK.dll $(OUTDIR)/MDATHUNK.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /Zp1 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /Zn /c
CPP_PROJ=/nologo /Zp1 /W3 /GX /YX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /FR$(INTDIR)/ /Zn /Fp$(OUTDIR)/"MDATHUNK.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinRel/
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /Iu /o$(OUTDIR)/"MDATHUNK.bsc" 
BSC32_SBRS= \
	$(INTDIR)/DLLENTRY.SBR \
	$(INTDIR)/DEBUGOUT.SBR

$(OUTDIR)/MDATHUNK.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DLL /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib thunk32.lib /NOLOGO /ENTRY:"DllEntryPoint" /SUBSYSTEM:windows /DLL /MACHINE:I386
# SUBTRACT LINK32 /INCREMENTAL:yes
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib thunk32.lib /NOLOGO\
 /ENTRY:"DllEntryPoint" /SUBSYSTEM:windows /DLL /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"MDATHUNK.pdb" /MACHINE:I386 /DEF:".\MDATHUNK.DEF"\
 /OUT:$(OUTDIR)/"MDATHUNK.dll" /IMPLIB:$(OUTDIR)/"MDATHUNK.lib" 
DEF_FILE=.\MDATHUNK.DEF
LINK32_OBJS= \
	$(INTDIR)/DLLENTRY.OBJ \
	$(INTDIR)/DEBUGOUT.OBJ \
	.\32TO16.OBJ

$(OUTDIR)/MDATHUNK.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "WinDebug"
# PROP Intermediate_Dir "WinDebug"
OUTDIR=.\WinDebug
INTDIR=.\WinDebug

ALL : $(OUTDIR)/MDATHUNK.dll $(OUTDIR)/MDATHUNK.bsc

$(OUTDIR) : 
    if not exist $(OUTDIR)/nul mkdir $(OUTDIR)

# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE CPP /nologo /MT /W3 /GX /Zi /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /c
# ADD CPP /nologo /Zp1 /W3 /GX /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /Zn /c
# SUBTRACT CPP /Z<none>
CPP_PROJ=/nologo /Zp1 /W3 /GX /YX /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /FR$(INTDIR)/ /Zn /Fp$(OUTDIR)/"MDATHUNK.pch" /Fo$(INTDIR)/ /c 
CPP_OBJS=.\WinDebug/
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /Iu /o$(OUTDIR)/"MDATHUNK.bsc" 
BSC32_SBRS= \
	$(INTDIR)/DLLENTRY.SBR \
	$(INTDIR)/DEBUGOUT.SBR

$(OUTDIR)/MDATHUNK.bsc : $(OUTDIR)  $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /NOLOGO /SUBSYSTEM:windows /DLL /DEBUG /MACHINE:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib thunk32.lib /NOLOGO /ENTRY:"DllEntryPoint" /SUBSYSTEM:windows /DLL /INCREMENTAL:no /MACHINE:I386
# SUBTRACT LINK32 /DEBUG
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib thunk32.lib /NOLOGO\
 /ENTRY:"DllEntryPoint" /SUBSYSTEM:windows /DLL /INCREMENTAL:no\
 /PDB:$(OUTDIR)/"MDATHUNK.pdb" /MACHINE:I386 /DEF:".\MDATHUNK.DEF"\
 /OUT:$(OUTDIR)/"MDATHUNK.dll" /IMPLIB:$(OUTDIR)/"MDATHUNK.lib" 
DEF_FILE=.\MDATHUNK.DEF
LINK32_OBJS= \
	$(INTDIR)/DLLENTRY.OBJ \
	$(INTDIR)/DEBUGOUT.OBJ \
	.\32TO16.OBJ

$(OUTDIR)/MDATHUNK.dll : $(OUTDIR)  $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Group "Sources"

################################################################################
# Begin Source File

SOURCE=.\DLLENTRY.C

$(INTDIR)/DLLENTRY.OBJ :  $(SOURCE)  $(INTDIR)

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DEBUGOUT.C

$(INTDIR)/DEBUGOUT.OBJ :  $(SOURCE)  $(INTDIR)

# End Source File
# End Group
################################################################################
# Begin Group "Libraries"

################################################################################
# Begin Source File

SOURCE=.\32TO16.OBJ
# End Source File
################################################################################
# Begin Source File

SOURCE=.\MDATHUNK.DEF
# End Source File
# End Group
# End Project
################################################################################
