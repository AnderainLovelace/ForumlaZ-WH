# Microsoft Developer Studio Project File - Name="FormulaZ" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=FormulaZ - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FormulaZ.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FormulaZ.mak" CFG="FormulaZ - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FormulaZ - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "FormulaZ - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FormulaZ - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "FormulaZ - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MD /W3 /Gm /GX /ZI /Od /I "./include" /I "./include/eigenmath" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 SDL.lib SDLmain.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "FormulaZ - Win32 Release"
# Name "FormulaZ - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\core\abs.c
# End Source File
# Begin Source File

SOURCE=.\src\core\add.c
# End Source File
# Begin Source File

SOURCE=.\src\core\adj.c
# End Source File
# Begin Source File

SOURCE=.\src\core\alloc.c
# End Source File
# Begin Source File

SOURCE=.\src\core\append.c
# End Source File
# Begin Source File

SOURCE=.\src\core\arccos.c
# End Source File
# Begin Source File

SOURCE=.\src\core\arccosh.c
# End Source File
# Begin Source File

SOURCE=.\src\core\arcsin.c
# End Source File
# Begin Source File

SOURCE=.\src\core\arcsinh.c
# End Source File
# Begin Source File

SOURCE=.\src\core\arctan.c
# End Source File
# Begin Source File

SOURCE=.\src\core\arctanh.c
# End Source File
# Begin Source File

SOURCE=.\src\core\arg.c
# End Source File
# Begin Source File

SOURCE=.\src\core\bake.c
# End Source File
# Begin Source File

SOURCE=.\src\core\besselj.c
# End Source File
# Begin Source File

SOURCE=.\src\core\bessely.c
# End Source File
# Begin Source File

SOURCE=.\src\core\bignum.c
# End Source File
# Begin Source File

SOURCE=.\src\core\binomial.c
# End Source File
# Begin Source File

SOURCE=.\src\core\ceiling.c
# End Source File
# Begin Source File

SOURCE=.\src\core\choose.c
# End Source File
# Begin Source File

SOURCE=.\src\core\circexp.c
# End Source File
# Begin Source File

SOURCE=.\src\core\clear.c
# End Source File
# Begin Source File

SOURCE=.\src\core\clock.c
# End Source File
# Begin Source File

SOURCE=.\src\core\coeff.c
# End Source File
# Begin Source File

SOURCE=.\src\core\cofactor.c
# End Source File
# Begin Source File

SOURCE=.\src\core\condense.c
# End Source File
# Begin Source File

SOURCE=.\src\core\conj.c
# End Source File
# Begin Source File

SOURCE=.\src\core\cons.c
# End Source File
# Begin Source File

SOURCE=.\src\core\contract.c
# End Source File
# Begin Source File

SOURCE=.\src\core\cos.c
# End Source File
# Begin Source File

SOURCE=.\src\core\cosh.c
# End Source File
# Begin Source File

SOURCE=.\src\core\data.c
# End Source File
# Begin Source File

SOURCE=.\src\core\decomp.c
# End Source File
# Begin Source File

SOURCE=.\src\core\define.c
# End Source File
# Begin Source File

SOURCE=.\src\core\defint.c
# End Source File
# Begin Source File

SOURCE=.\src\core\degree.c
# End Source File
# Begin Source File

SOURCE=.\src\core\denominator.c
# End Source File
# Begin Source File

SOURCE=.\src\core\derivative.c
# End Source File
# Begin Source File

SOURCE=.\src\core\det.c
# End Source File
# Begin Source File

SOURCE=.\src\core\dirac.c
# End Source File
# Begin Source File

SOURCE=.\src\core\display.c
# End Source File
# Begin Source File

SOURCE=.\src\core\distill.c
# End Source File
# Begin Source File

SOURCE=.\src\core\divisors.c
# End Source File
# Begin Source File

SOURCE=.\src\core\dpow.c
# End Source File
# Begin Source File

SOURCE=.\src\core\draw.c
# End Source File
# Begin Source File

SOURCE=.\src\core\dsolve.c
# End Source File
# Begin Source File

SOURCE=.\src\core\eigen.c
# End Source File
# Begin Source File

SOURCE=.\src\core\erf.c
# End Source File
# Begin Source File

SOURCE=.\src\core\erfc.c
# End Source File
# Begin Source File

SOURCE=.\src\core\eval.c
# End Source File
# Begin Source File

SOURCE=.\src\core\expand.c
# End Source File
# Begin Source File

SOURCE=.\src\core\expcos.c
# End Source File
# Begin Source File

SOURCE=.\src\core\expsin.c
# End Source File
# Begin Source File

SOURCE=.\src\core\factor.c
# End Source File
# Begin Source File

SOURCE=.\src\core\factorial.c
# End Source File
# Begin Source File

SOURCE=.\src\core\factorpoly.c
# End Source File
# Begin Source File

SOURCE=.\src\core\factors.c
# End Source File
# Begin Source File

SOURCE=.\src\core\filter.c
# End Source File
# Begin Source File

SOURCE=.\src\core\find.c
# End Source File
# Begin Source File

SOURCE=.\src\core\float.c
# End Source File
# Begin Source File

SOURCE=.\src\core\floor.c
# End Source File
# Begin Source File

SOURCE=.\src\font.c
# End Source File
# Begin Source File

SOURCE=.\src\core\for.c
# End Source File
# Begin Source File

SOURCE=.\src\core\gamma.c
# End Source File
# Begin Source File

SOURCE=.\src\core\gcd.c
# End Source File
# Begin Source File

SOURCE=.\src\core\guess.c
# End Source File
# Begin Source File

SOURCE=.\src\core\hermite.c
# End Source File
# Begin Source File

SOURCE=.\src\core\hilbert.c
# End Source File
# Begin Source File

SOURCE=.\src\core\imag.c
# End Source File
# Begin Source File

SOURCE=.\src\core\index.c
# End Source File
# Begin Source File

SOURCE=.\src\core\init.c
# End Source File
# Begin Source File

SOURCE=.\src\core\inner.c
# End Source File
# Begin Source File

SOURCE=.\src\core\integral.c
# End Source File
# Begin Source File

SOURCE=.\src\core\inv.c
# End Source File
# Begin Source File

SOURCE=.\src\io.c
# End Source File
# Begin Source File

SOURCE=.\src\core\is.c
# End Source File
# Begin Source File

SOURCE=.\src\core\isprime.c
# End Source File
# Begin Source File

SOURCE=.\src\core\itab.c
# End Source File
# Begin Source File

SOURCE=.\src\core\itest.c
# End Source File
# Begin Source File

SOURCE=.\src\core\laguerre.c
# End Source File
# Begin Source File

SOURCE=.\src\core\laplace.c
# End Source File
# Begin Source File

SOURCE=.\src\core\lcm.c
# End Source File
# Begin Source File

SOURCE=.\src\core\leading.c
# End Source File
# Begin Source File

SOURCE=.\src\core\legendre.c
# End Source File
# Begin Source File

SOURCE=.\src\core\list.c
# End Source File
# Begin Source File

SOURCE=.\src\core\log.c
# End Source File
# Begin Source File

SOURCE=.\src\core\madd.c
# End Source File
# Begin Source File

SOURCE=.\src\core\mag.c
# End Source File
# Begin Source File

SOURCE=.\src\main.c
# End Source File
# Begin Source File

SOURCE=.\src\core\mcmp.c
# End Source File
# Begin Source File

SOURCE=.\src\core\mfactor.c
# End Source File
# Begin Source File

SOURCE=.\src\core\mgcd.c
# End Source File
# Begin Source File

SOURCE=".\src\core\mini-test.c"
# End Source File
# Begin Source File

SOURCE=.\src\core\misc.c
# End Source File
# Begin Source File

SOURCE=.\src\core\mmodpow.c
# End Source File
# Begin Source File

SOURCE=.\src\core\mmul.c
# End Source File
# Begin Source File

SOURCE=.\src\core\mod.c
# End Source File
# Begin Source File

SOURCE=.\src\core\mpow.c
# End Source File
# Begin Source File

SOURCE=.\src\core\mprime.c
# End Source File
# Begin Source File

SOURCE=.\src\core\mroot.c
# End Source File
# Begin Source File

SOURCE=.\src\core\mscan.c
# End Source File
# Begin Source File

SOURCE=.\src\core\msqrt.c
# End Source File
# Begin Source File

SOURCE=.\src\core\mstr.c
# End Source File
# Begin Source File

SOURCE=.\src\core\multiply.c
# End Source File
# Begin Source File

SOURCE=.\src\core\nroots.c
# End Source File
# Begin Source File

SOURCE=.\src\core\numerator.c
# End Source File
# Begin Source File

SOURCE=.\src\core\outer.c
# End Source File
# Begin Source File

SOURCE=.\src\core\partition.c
# End Source File
# Begin Source File

SOURCE=.\src\core\polar.c
# End Source File
# Begin Source File

SOURCE=.\src\core\pollard.c
# End Source File
# Begin Source File

SOURCE=.\src\core\power.c
# End Source File
# Begin Source File

SOURCE=.\src\core\prime.c
# End Source File
# Begin Source File

SOURCE=.\src\core\primetab.c
# End Source File
# Begin Source File

SOURCE=.\src\core\print.c
# End Source File
# Begin Source File

SOURCE=.\src\core\product.c
# End Source File
# Begin Source File

SOURCE=.\src\core\qadd.c
# End Source File
# Begin Source File

SOURCE=.\src\core\qdiv.c
# End Source File
# Begin Source File

SOURCE=.\src\core\qmul.c
# End Source File
# Begin Source File

SOURCE=.\src\core\qpow.c
# End Source File
# Begin Source File

SOURCE=.\src\core\qsub.c
# End Source File
# Begin Source File

SOURCE=.\src\core\quickfactor.c
# End Source File
# Begin Source File

SOURCE=.\src\core\quotient.c
# End Source File
# Begin Source File

SOURCE=.\src\core\rationalize.c
# End Source File
# Begin Source File

SOURCE=.\src\core\real.c
# End Source File
# Begin Source File

SOURCE=.\src\core\rect.c
# End Source File
# Begin Source File

SOURCE=.\src\core\rewrite.c
# End Source File
# Begin Source File

SOURCE=.\src\core\roots.c
# End Source File
# Begin Source File

SOURCE=.\src\core\run.c
# End Source File
# Begin Source File

SOURCE=.\src\core\scan.c
# End Source File
# Begin Source File

SOURCE=.\src\core\selftest.c
# End Source File
# Begin Source File

SOURCE=.\src\core\sgn.c
# End Source File
# Begin Source File

SOURCE=.\src\core\simfac.c
# End Source File
# Begin Source File

SOURCE=.\src\core\simplify.c
# End Source File
# Begin Source File

SOURCE=.\src\core\sin.c
# End Source File
# Begin Source File

SOURCE=.\src\core\sinh.c
# End Source File
# Begin Source File

SOURCE=.\src\core\stack.c
# End Source File
# Begin Source File

SOURCE=.\src\core\subst.c
# End Source File
# Begin Source File

SOURCE=.\src\core\sum.c
# End Source File
# Begin Source File

SOURCE=.\src\core\symbol.c
# End Source File
# Begin Source File

SOURCE=.\src\core\tan.c
# End Source File
# Begin Source File

SOURCE=.\src\core\tanh.c
# End Source File
# Begin Source File

SOURCE=.\src\core\taylor.c
# End Source File
# Begin Source File

SOURCE=.\src\core\tensor.c
# End Source File
# Begin Source File

SOURCE=.\src\core\test.c
# End Source File
# Begin Source File

SOURCE=.\src\core\transform.c
# End Source File
# Begin Source File

SOURCE=.\src\core\transpose.c
# End Source File
# Begin Source File

SOURCE=.\src\ufx\ufxfile.c
# End Source File
# Begin Source File

SOURCE=.\src\ufx\ufxgraph.c
# End Source File
# Begin Source File

SOURCE=.\src\ufx\ufxkey.c
# End Source File
# Begin Source File

SOURCE=.\src\core\userfunc.c
# End Source File
# Begin Source File

SOURCE=.\src\core\variables.c
# End Source File
# Begin Source File

SOURCE=.\src\core\vectorize.c
# End Source File
# Begin Source File

SOURCE=.\src\core\zero.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\eigenmath\defs.h
# End Source File
# Begin Source File

SOURCE=.\include\font.h
# End Source File
# Begin Source File

SOURCE=.\include\eigenmath\help.h
# End Source File
# Begin Source File

SOURCE=.\include\eigenmath\prototypes.h
# End Source File
# Begin Source File

SOURCE=.\include\eigenmath\selftest.h
# End Source File
# Begin Source File

SOURCE=.\include\eigenmath\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\include\ufxkeycode.h
# End Source File
# Begin Source File

SOURCE=.\include\ufxlib.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
