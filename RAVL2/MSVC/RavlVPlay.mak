


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" /I "C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include" /I "C:\GTKWIN32\lib\gtk-2.0\include" /I "C:\GTKWIN32\lib\glib-2.0\include" /I "C:\GTKWIN32\include\cairo" /I "C:\GTKWIN32\include\gtk-2.0" /I "C:\GTKWIN32\include\glib-2.0" /I "C:\GTKWIN32\include\pango-1.0" /I "C:\GTKWIN32\include\atk-1.0" /I "C:\GTKWIN32\include\gtkglext-1.0" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlVPlay
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlVPlay
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setupRavlVPlay  $(OPTOBJDIR)/GUIPlayControl.obj
	@echo -- making $(OPTLIBDIR)/RavlVPlay.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlVPlay.lib $(OPTOBJDIR)/*.obj


debug:: setupRavlVPlay  $(DEBUGOBJDIR)/GUIPlayControl.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlVPlay.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlVPlay.lib $(DEBUGOBJDIR)/*.obj

setupRavlVPlay::
        echo --- creating dir for RavlVPlay
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/GUIPlayControl.obj: .././Applications/VPlay/GUIPlayControl.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GUIPlayControl.obj .././Applications/VPlay/GUIPlayControl.cc

$(DEBUGOBJDIR)/GUIPlayControl.obj: .././Applications/VPlay/GUIPlayControl.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GUIPlayControl.obj .././Applications/VPlay/GUIPlayControl.cc


