# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Mdadebug - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Mdadebug - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Mdadebug - Win32 Release" && "$(CFG)" !=\
 "Mdadebug - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Mdadebug.mak" CFG="Mdadebug - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Mdadebug - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Mdadebug - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Mdadebug - Win32 Release"

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

ALL : "$(OUTDIR)\Mdadebug.exe"

CLEAN : 
	-@erase ".\WinRel\Mdadebug.exe"
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

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

$(OUTDIR)/MDADEBUG.bsc : $(OUTDIR)  $(BSC32_SBRS)
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /Zp1 /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /c
# SUBTRACT CPP /Fr /YX
CPP_PROJ=/nologo /Zp1 /ML /W3 /WX /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\WinRel/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
RSC_PROJ=/l 0x809 /fo"$(INTDIR)/APP.res" /d "NDEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Mdadebug.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 ctl3d32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /incremental:yes
LINK32_FLAGS=ctl3d32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/Mdadebug.pdb" /machine:I386\
 /def:".\APP.DEF" /out:"$(OUTDIR)/Mdadebug.exe" 
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
	"$(INTDIR)/APP.res" \
	"..\DLL\WINDEBUG\MDATHUNK.lib"

"$(OUTDIR)\Mdadebug.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Mdadebug - Win32 Debug"

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

ALL : "$(OUTDIR)\Mdadebug.exe"

CLEAN : 
	-@erase ".\WinDebug\Mdadebug.exe"
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
	-@erase ".\WinDebug\Mdadebug.pdb"
	-@erase ".\WinDebug\vc40.pdb"
	-@erase ".\WinDebug\vc40.idb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

# ADD BASE CPP /nologo /W3 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /FR /YX /c
# ADD CPP /nologo /Zp1 /W3 /WX /Gm /GX /Zi /Od /Gf /Gy /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "DEBUG" /Zn /c
# SUBTRACT CPP /Fr /YX
CPP_PROJ=/nologo /Zp1 /MLd /W3 /WX /Gm /GX /Zi /Od /Gf /Gy /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "DEBUG" /Fo"$(INTDIR)/" /Fd"$(INTDIR)/" /Zn /c 
CPP_OBJS=.\WinDebug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
RSC_PROJ=/l 0x809 /fo"$(INTDIR)/APP.res" /d "_DEBUG" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Mdadebug.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 ctl3d32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386
LINK32_FLAGS=ctl3d32.lib kernel32.lib user32.lib gdi32.lib winspool.lib\
 comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib /nologo\
 /subsystem:windows /incremental:no /pdb:"$(OUTDIR)/Mdadebug.pdb" /debug\
 /machine:I386 /def:".\APP.DEF" /out:"$(OUTDIR)/Mdadebug.exe" 
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
	"$(INTDIR)/APP.res" \
	"..\DLL\WINDEBUG\MDATHUNK.lib"

"$(OUTDIR)\Mdadebug.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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

# Name "Mdadebug - Win32 Release"
# Name "Mdadebug - Win32 Debug"

!IF  "$(CFG)" == "Mdadebug - Win32 Release"

!ELSEIF  "$(CFG)" == "Mdadebug - Win32 Debug"

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


# End Source File
################################################################################
# Begin Source File

SOURCE=.\DEBUG.C

"$(INTDIR)\DEBUG.OBJ" : $(SOURCE) "$(INTDIR)"


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


# End Source File
################################################################################
# Begin Source File

SOURCE=.\APP.DEF

!IF  "$(CFG)" == "Mdadebug - Win32 Release"

!ELSEIF  "$(CFG)" == "Mdadebug - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=\DEV\MONODBG\MDADEBUG\DLL\WINDEBUG\MDATHUNK.lib

!IF  "$(CFG)" == "Mdadebug - Win32 Release"

!ELSEIF  "$(CFG)" == "Mdadebug - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\APP.RC
DEP_RSC_APP_R=\
	".\APP.ICO"\
	".\APP.BMP"\
	".\MENURSC.H"\
	".\STRNGRSC.H"\
	

"$(INTDIR)\APP.res" : $(SOURCE) $(DEP_RSC_APP_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
# End Target
# End Project
################################################################################
