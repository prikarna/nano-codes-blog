@rem +-------------------------------------------------------------+
@rem   Batch file to build Mini project for "3 stages compile"
@rem   To run this, just type Make_3 <param> then press <Enter>
@rem   <param> is one of : all, clean and rebuild
@rem   If no <param> specified then the default is all
@rem +-------------------------------------------------------------+


@echo *** Building ErrMini project for DT-NUC120 microcontroller
@echo.

@setlocal

@set MAKE_REBUILD=0
@set MAKE_PARM="%1"

@set CORT_VER=m0
@set TGT_CPU=arm_cortex_%CORT_VER%
@set PROJ_NAME=ErrMini

@set SOLUTION_DIR=D:\Microcontroller\DtNuc120_ErrMini
@set PROJ_DIR=%SOLUTION_DIR%\%PROJ_NAME%
@set BIN_DIR=%PROJ_DIR%\Bin
@set GCC_BIN_DIR=D:\Microcontroller\gcc-arm\bin
@set OBJ_DIR=%PROJ_DIR%\Obj

@if %MAKE_PARM%=="clean" goto CLEAN
@if %MAKE_PARM%=="rebuild" goto REBUILD


@rem +------------------------------------------------------+
@rem   Make all
@rem +------------------------------------------------------+

:ALL

@set TGT=%PROJ_NAME%.bin
@set ELF=%PROJ_NAME%.elf
@set SRC_DIR=%PROJ_DIR%

@path=%path%;%GCC_BIN_DIR%

@set SRCS=%SRC_DIR%\CMSIS.c
@set SRCS=%SRCS% %SRC_DIR%\Main.c

@set OBJS=%OBJ_DIR%\CMSIS.o
@set OBJS=%OBJS% %OBJ_DIR%\Main.o

@set CC=arm-none-eabi-gcc.exe

@set CC_OPTS=-Wall -D_DEBUG -g -O0
@set CC_OPTS=%CC_OPTS% -mcpu=cortex-%CORT_VER% -mthumb
@set CC_OPTS=%CC_OPTS% -ffunction-sections
@set CC_OPTS=%CC_OPTS% -isystem%SOLUTION_DIR%\DkSys
@set CC_OPTS=%CC_OPTS% -c

@set LNK=arm-none-eabi-ld.exe

@set LNK_OPTS=%LNK_OPTS% -Map=%BIN_DIR%\%PROJ_NAME%.map
@set LNK_OPTS=%LNK_OPTS% --gc-sections
@set LNK_OPTS=%LNK_OPTS% -L%GCC_BIN_DIR%\..\lib\gcc\arm-none-eabi\6.2.1\thumb\v6-m
@set LNK_OPTS=%LNK_OPTS% -L%GCC_BIN_DIR%\..\arm-none-eabi\lib\thumb\v6-m
@set LNK_OPTS=%LNK_OPTS% -T%PROJ_DIR%\%PROJ_NAME%.ld
@set LNK_OPTS=%LNK_OPTS% -o%BIN_DIR%\%ELF%

@set LNK_OPTS_EXT=-lgcc -lg -lc

@set GEN_BIN=arm-none-eabi-objcopy.exe
@set GEN_BIN_OPT=-Obinary

@prompt [$T]$S

@echo Preparing...
@if not exist %BIN_DIR% mkdir %BIN_DIR%
@if not exist %OBJ_DIR% mkdir %OBJ_DIR%

@echo.
@echo Compiling...
@cd /d %OBJ_DIR%
@for %%s in (%SRCS%) do %CC% %CC_OPTS% %%s
@if errorlevel 1 goto END
@cd ..

@echo.
@echo Linking...
%LNK% %LNK_OPTS% %OBJS% %LNK_OPTS_EXT%
@if errorlevel 1 goto END

@echo.
@echo Generating binary...
%GEN_BIN% %GEN_BIN_OPT% %BIN_DIR%\%ELF% %BIN_DIR%\%TGT%
@if errorlevel 1 goto END

@echo.
@echo SUCCEEDED :
@dir %BIN_DIR%\%TGT% | findstr %TGT%
@goto END


@rem +------------------------------------------------------+
@rem   Make clean
@rem +------------------------------------------------------+

:CLEAN
@echo Cleaning up...
@echo.
@if exist %BIN_DIR% erase /S /Q %BIN_DIR%\*.*
@if exist %OBJ_DIR% erase /S /Q %OBJ_DIR%\*.*
@if %MAKE_REBUILD%==1 goto ALL
@goto END


@rem +------------------------------------------------------+
@rem   Make rebuild
@rem +------------------------------------------------------+

:REBUILD
@set MAKE_REBUILD=1
@goto CLEAN

:END
@endlocal
