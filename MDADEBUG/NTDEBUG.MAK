# Microsoft Developer Studio Generated NMAKE File, Format Version 40001
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Ntdebug - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Ntdebug - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Ntdebug - Win32 Release" && "$(CFG)" !=\
 "Ntdebug - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ntdebug.mak" CFG="Ntdebug - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ntdebug - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Ntdebug - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
CPP=cl.exe
MTL=mktyplib.exe
RSC=rc.exe

!IF  "$(CFG)" == "Ntdebug - Win32 Release"

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

ALL : "$(OUTDIR)\Ntdebug.exe" "$(OUTDIR)\Ntdebug.bsc"

CLEAN : 
	-@erase ".\WinRel\Ntdebug.exe"
	-@erase ".\WinRel\APPWND.OBJ"
	-@erase ".\WinRel\ABOUTDLG.OBJ"
	-@erase ".\WinRel\WINUTILS.OBJ"
	-@erase ".\WinRel\DILWND.OBJ"
	-@erase ".\WinRel\DEBUG.OBJ"
	-@erase ".\WinRel\CLNTWND.OBJ"
	-@erase ".\WinRel\WINMAIN.OBJ"
	-@erase ".\WinRel\SETAPDLG.OBJ"
	-@erase ".\WinRel\DBGOUT.OBJ"
	-@erase ".\WinRel\APP.res"
	-@erase ".\WinRel\Ntdebug.bsc"
	-@erase ".\WinRel\APPWND.SBR"
	-@erase ".\WinRel\ABOUTDLG.SBR"
	-@erase ".\WinRel\WINUTILS.SBR"
	-@erase ".\WinRel\DILWND.SBR"
	-@erase ".\WinRel\DEBUG.SBR"
	-@erase ".\WinRel\CLNTWND.SBR"
	-@erase ".\WinRel\WINMAIN.SBR"
	-@erase ".\WinRel\SETAPDLG.SBR"
	-@erase ".\WinRel\DBGOUT.SBR"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/NTDEBUG.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /Zp1 /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Fr /c
# SUBTRACT CPP /YX
CPP_PROJ=/nologo /Zp1 /ML /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fr"$(INTDIR)/" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=.\WinRel/
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
RSC_PROJ=/l 0x809 /fo"$(INTDIR)/APP.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Ntdebug.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/APPWND.SBR" \
	"$(INTDIR)/ABOUTDLG.SBR" \
	"$(INTDIR)/WINUTILS.SBR" \
	"$(INTDIR)/DILWND.SBR" \
	"$(INTDIR)/DEBUG.SBR" \
	"$(INTDIR)/CLNTWND.SBR" \
	"$(INTDIR)/WINMAIN.SBR" \
	"$(INTDIR)/SETAPDLG.SBR" \
	"$(INTDIR)/DBGOUT.SBR"

"$(OUTDIR)\Ntdebug.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /incremental:yes
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/Ntdebug.pdb" /machine:I386\
 /def:".\APP.DEF" /out:"$(OUTDIR)/Ntdebug.exe" 
DEF_FILE= \
	".\APP.DEF"
LINK32_OBJS= \
	"$(INTDIR)/APPWND.OBJ" \
	"$(INTDIR)/ABOUTDLG.OBJ" \
	"$(INTDIR)/WINUTILS.OBJ" \
	"$(INTDIR)/DILWND.OBJ" \
	"$(INTDIR)/DEBUG.OBJ" \
	"$(INTDIR)/CLNTWND.OBJ" \
	"$(INTDIR)/WINMAIN.OBJ" \
	"$(INTDIR)/SETAPDLG.OBJ" \
	"$(INTDIR)/DBGOUT.OBJ" \
	"$(INTDIR)/APP.res"

"$(OUTDIR)\Ntdebug.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Ntdebug - Win32 Debug"

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

ALL : "$(OUTDIR)\Ntdebug.exe" "$(OUTDIR)\Ntdebug.bsc"

CLEAN : 
	-@erase ".\WinDebug\Ntdebug.exe"
	-@erase ".\WinDebug\APPWND.OBJ"
	-@erase ".\WinDebug\ABOUTDLG.OBJ"
	-@erase ".\WinDebug\WINUTILS.OBJ"
	-@erase ".\WinDebug\DILWND.OBJ"
	-@erase ".\WinDebug\DEBUG.OBJ"
	-@erase ".\WinDebug\CLNTWND.OBJ"
	-@erase ".\WinDebug\WINMAIN.OBJ"
	-@erase ".\WinDebug\SETAPDLG.OBJ"
	-@erase ".\WinDebug\DBGOUT.OBJ"
	-@erase ".\WinDebug\APP.res"
	-@erase ".\WinDebug\Ntdebug.pdb"
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\vc40.idb"
	-@erase ".\WinDebug\Ntdebug.bsc"
	-@erase ".\WinDebug\APPWND.SBR"
	-@erase ".\WinDebug\ABOUTDLG.SBR"
	-@erase ".\WinDebug\WINUTILS.SBR"
	-@erase ".\WinDebug\DILWND.SBR"
	-@erase ".\WinDebug\DEBUG.SBR"
	-@erase ".\WinDebug\CLNTWND.SBR"
	-@erase ".\WinDebug\WINMAIN.SBR"
	-@erase ".\WinDebug\SETAPDLG.SBR"
	-@erase ".\WinDebug\DBGOUT.SBR"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /Zp1 /W3 /WX /Gm /GX /Zi /Od /Gf /Gy /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "DEBUG" /FR /Zn /c
# SUBTRACT CPP /YX
CPP_PROJ=/nologo /Zp1 /MLd /W3 /WX /Gm /GX /Zi /Od /Gf /Gy /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "DEBUG" /FR"$(INTDIR)/" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /Zn /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=.\WinDebug/
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
RSC_PROJ=/l 0x809 /fo"$(INTDIR)/APP.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Ntdebug.bsc" 
BSC32_SBRS= \
	"$(INTDIR)/APPWND.SBR" \
	"$(INTDIR)/ABOUTDLG.SBR" \
	"$(INTDIR)/WINUTILS.SBR" \
	"$(INTDIR)/DILWND.SBR" \
	"$(INTDIR)/DEBUG.SBR" \
	"$(INTDIR)/CLNTWND.SBR" \
	"$(INTDIR)/WINMAIN.SBR" \
	"$(INTDIR)/SETAPDLG.SBR" \
	"$(INTDIR)/DBGOUT.SBR"

"$(OUTDIR)\Ntdebug.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib\
 advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/Ntdebug.pdb" /debug\
 /machine:I386 /def:".\APP.DEF" /out:"$(OUTDIR)/Ntdebug.exe" 
DEF_FILE= \
	".\APP.DEF"
LINK32_OBJS= \
	"$(INTDIR)/APPWND.OBJ" \
	"$(INTDIR)/ABOUTDLG.OBJ" \
	"$(INTDIR)/WINUTILS.OBJ" \
	"$(INTDIR)/DILWND.OBJ" \
	"$(INTDIR)/DEBUG.OBJ" \
	"$(INTDIR)/CLNTWND.OBJ" \
	"$(INTDIR)/WINMAIN.OBJ" \
	"$(INTDIR)/SETAPDLG.OBJ" \
	"$(INTDIR)/DBGOUT.OBJ" \
	"$(INTDIR)/APP.res"

"$(OUTDIR)\Ntdebug.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Ntdebug - Win32 Release"
# Name "Ntdebug - Win32 Debug"

!IF  "$(CFG)" == "Ntdebug - Win32 Release"

!ELSEIF  "$(CFG)" == "Ntdebug - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\APPWND.C
DEP_CPP_APPWN=\
	".\AF.H"\
	".\WINUTILS.H"\
	".\MENURSC.H"\
	".\STRNGRSC.H"\
	".\BASEDEFS.H"\
	".\DEBUG.H"\
	

"$(INTDIR)\APPWND.OBJ" : $(SOURCE) $(DEP_CPP_APPWN) "$(INTDIR)"

"$(INTDIR)\APPWND.SBR" : $(SOURCE) $(DEP_CPP_APPWN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ABOUTDLG.C
DEP_CPP_ABOUT=\
	".\AF.H"\
	".\WINUTILS.H"\
	".\BASEDEFS.H"\
	".\DEBUG.H"\
	

"$(INTDIR)\ABOUTDLG.OBJ" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"

"$(INTDIR)\ABOUTDLG.SBR" : $(SOURCE) $(DEP_CPP_ABOUT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WINUTILS.C
DEP_CPP_WINUT=\
	".\AF.H"\
	".\WINUTILS.H"\
	".\BASEDEFS.H"\
	".\DEBUG.H"\
	

"$(INTDIR)\WINUTILS.OBJ" : $(SOURCE) $(DEP_CPP_WINUT) "$(INTDIR)"

"$(INTDIR)\WINUTILS.SBR" : $(SOURCE) $(DEP_CPP_WINUT) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DILWND.C
DEP_CPP_DILWN=\
	".\AF.H"\
	".\WINUTILS.H"\
	".\MENURSC.H"\
	".\STRNGRSC.H"\
	".\BASEDEFS.H"\
	".\DEBUG.H"\
	

"$(INTDIR)\DILWND.OBJ" : $(SOURCE) $(DEP_CPP_DILWN) "$(INTDIR)"

"$(INTDIR)\DILWND.SBR" : $(SOURCE) $(DEP_CPP_DILWN) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DEBUG.C

"$(INTDIR)\DEBUG.OBJ" : $(SOURCE) "$(INTDIR)"

"$(INTDIR)\DEBUG.SBR" : $(SOURCE) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CLNTWND.C
DEP_CPP_CLNTW=\
	".\AF.H"\
	".\WINUTILS.H"\
	".\MENURSC.H"\
	".\STRNGRSC.H"\
	".\BASEDEFS.H"\
	".\DEBUG.H"\
	

"$(INTDIR)\CLNTWND.OBJ" : $(SOURCE) $(DEP_CPP_CLNTW) "$(INTDIR)"

"$(INTDIR)\CLNTWND.SBR" : $(SOURCE) $(DEP_CPP_CLNTW) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\WINMAIN.C
DEP_CPP_WINMA=\
	".\AF.H"\
	".\WINUTILS.H"\
	".\STRNGRSC.H"\
	".\BASEDEFS.H"\
	".\DEBUG.H"\
	

"$(INTDIR)\WINMAIN.OBJ" : $(SOURCE) $(DEP_CPP_WINMA) "$(INTDIR)"

"$(INTDIR)\WINMAIN.SBR" : $(SOURCE) $(DEP_CPP_WINMA) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\SETAPDLG.C
DEP_CPP_SETAP=\
	".\AF.H"\
	".\WINUTILS.H"\
	".\BASEDEFS.H"\
	".\DEBUG.H"\
	

"$(INTDIR)\SETAPDLG.OBJ" : $(SOURCE) $(DEP_CPP_SETAP) "$(INTDIR)"

"$(INTDIR)\SETAPDLG.SBR" : $(SOURCE) $(DEP_CPP_SETAP) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DBGOUT.C
DEP_CPP_DBGOU=\
	".\AF.H"\
	".\MENURSC.H"\
	".\BASEDEFS.H"\
	".\DEBUG.H"\
	

"$(INTDIR)\DBGOUT.OBJ" : $(SOURCE) $(DEP_CPP_DBGOU) "$(INTDIR)"

"$(INTDIR)\DBGOUT.SBR" : $(SOURCE) $(DEP_CPP_DBGOU) "$(INTDIR)"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\APP.DEF

!IF  "$(CFG)" == "Ntdebug - Win32 Release"

!ELSEIF  "$(CFG)" == "Ntdebug - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\APP.RC
DEP_RSC_APP_R=\
	".\APP.ICO"\
	".\MENURSC.H"\
	".\STRNGRSC.H"\
	

"$(INTDIR)\APP.res" : $(SOURCE) $(DEP_RSC_APP_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
