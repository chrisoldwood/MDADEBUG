# Microsoft Visual C++ generated build script - Do not modify

PROJ = MDALIB16
DEBUG = 0
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = -d_DEBUG
R_RCDEFINES = -dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\DEV\MONODBG\MDADEBUG\MDALIB16\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC = MDABASE.C   
FIRSTCPP =             
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /Zp1 /W3 /ALw /Od /D "_DEBUG" /FR /Zn /GD 
CFLAGS_R_WDLL = /nologo /Gs /G3 /Zp1 /W3 /ALw /O2 /D "NDEBUG" /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /MAP:FULL
LIBS_D_WDLL = libw ldllcew oldnames 
LIBS_R_WDLL = libw ldllcew oldnames 
RCFLAGS = /nologo
RESFLAGS = /nologo
RUNFLAGS = 
DEFFILE = MDALIB16.DEF
OBJS_EXT = 32TO16.OBJ 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WDLL)
LFLAGS = $(LFLAGS_D_WDLL)
LIBS = $(LIBS_D_WDLL)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WDLL)
LFLAGS = $(LFLAGS_R_WDLL)
LIBS = $(LIBS_R_WDLL)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = MDATHUNK.SBR \
		MDABASE.SBR \
		MDAMAIN.SBR \
		MDAFILL.SBR \
		MDAFRAME.SBR \
		MDASCROL.SBR \
		MDASTRNG.SBR


32TO16_DEP = 

MDATHUNK_DEP = c:\dev\monodbg\mdadebug\mdalib16\mdalib.h \
	c:\dev\monodbg\mdadebug\mdalib16\mdadefs.h \
	c:\dev\monodbg\mdadebug\mdalib16\mdafuncs.h


MDABASE_DEP = c:\dev\monodbg\mdadebug\mdalib16\mdadefs.h


MDAMAIN_DEP = c:\dev\monodbg\mdadebug\mdalib16\mdadefs.h \
	c:\dev\monodbg\mdadebug\mdalib16\mdafuncs.h


MDAFILL_DEP = c:\dev\monodbg\mdadebug\mdalib16\mdadefs.h


MDAFRAME_DEP = c:\dev\monodbg\mdadebug\mdalib16\mdalib.h \
	c:\dev\monodbg\mdadebug\mdalib16\mdadefs.h \
	c:\dev\monodbg\mdadebug\mdalib16\mdafuncs.h


MDASCROL_DEP = c:\dev\monodbg\mdadebug\mdalib16\mdadefs.h


MDASTRNG_DEP = c:\dev\monodbg\mdadebug\mdalib16\mdadefs.h


all:	$(PROJ).DLL

MDATHUNK.OBJ:	MDATHUNK.C $(MDATHUNK_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c MDATHUNK.C

MDABASE.OBJ:	MDABASE.C $(MDABASE_DEP)
	$(CC) $(CFLAGS) $(CCREATEPCHFLAG) /c MDABASE.C

MDAMAIN.OBJ:	MDAMAIN.C $(MDAMAIN_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c MDAMAIN.C

MDAFILL.OBJ:	MDAFILL.C $(MDAFILL_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c MDAFILL.C

MDAFRAME.OBJ:	MDAFRAME.C $(MDAFRAME_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c MDAFRAME.C

MDASCROL.OBJ:	MDASCROL.C $(MDASCROL_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c MDASCROL.C

MDASTRNG.OBJ:	MDASTRNG.C $(MDASTRNG_DEP)
	$(CC) $(CFLAGS) $(CUSEPCHFLAG) /c MDASTRNG.C


$(PROJ).DLL::	MDATHUNK.OBJ MDABASE.OBJ MDAMAIN.OBJ MDAFILL.OBJ MDAFRAME.OBJ MDASCROL.OBJ \
	MDASTRNG.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
MDATHUNK.OBJ +
MDABASE.OBJ +
MDAMAIN.OBJ +
MDAFILL.OBJ +
MDAFRAME.OBJ +
MDASCROL.OBJ +
MDASTRNG.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
S:\PUBLIC\VC151\LIB\+
S:\PUBLIC\VC151\MFC\LIB\+
lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) $@
	implib /nowep $(PROJ).LIB $(PROJ).DLL


run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
