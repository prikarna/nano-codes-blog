@rem +---------------------------------------------------------+
@rem   Batch file to build Mini project
@rem   To run this, just type Make <param> then press <Enter>
@rem   <param> is one of : all, clean and rebuild
@rem   If no <param> specified then the default is all
@rem +---------------------------------------------------------+


@echo *** Building ErrMini project for DT-NUC120 microcontroller
@echo.

@setlocal

@set CORT_VER=m0
@set TGT_CPU=arm_cortex_%CORT_VER%
@set PROJ_NAME=ErrMini

@set SOLUTION_DIR=D:\Microcontroller\DtNuc120_ErrMini
@set PROJ_DIR=%SOLUTION_DIR%\%PROJ_NAME%
@set BIN_DIR=%PROJ_DIR%\Bin
@set GCC_BIN_DIR=D:\Microcontroller\gcc-arm\bin

@set MAKE_REBUILD=0
@set MAKE_PARM="%1"

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

@set CC=arm-none-eabi-gcc.exe

@set CC_LNK_OPTS=-Wall -D_DEBUG -g -O0
@set CC_LNK_OPTS=%CC_LNK_OPTS% -mcpu=cortex-%CORT_VER% -mthumb
@set CC_LNK_OPTS=%CC_LNK_OPTS% -ffunction-sections
@set CC_LNK_OPTS=%CC_LNK_OPTS% -isystem%SOLUTION_DIR%\DkSys
@set CC_LNK_OPTS=%CC_LNK_OPTS% -Wl,-Map=%BIN_DIR%\%PROJ_NAME%.map
@set CC_LNK_OPTS=%CC_LNK_OPTS% -Wl,--gc-sections
@set CC_LNK_OPTS=%CC_LNK_OPTS% -Wl,-L%PROJ_DIR%
@set CC_LNK_OPTS=%CC_LNK_OPTS% -Wl,-T%PROJ_DIR%\Mini.ld
@set CC_LNK_OPTS=%CC_LNK_OPTS% -Wl,-o%BIN_DIR%\%ELF%

@set GEN_BIN=arm-none-eabi-objcopy.exe
@set GEN_BIN_OPT=-Obinary

@prompt [$T]$S

@echo Preparing...
@if not exist %BIN_DIR% mkdir %BIN_DIR%
@if %errorlevel% equ 1 goto END

@echo.
@echo Compiling and linking...
%CC% %CC_LNK_OPTS% %SRCS%
@if %errorlevel% equ 1 goto END

@echo.
@echo Generating binary...
%GEN_BIN% %GEN_BIN_OPT% %BIN_DIR%\%ELF% %BIN_DIR%\%TGT%
@if %errorlevel% equ 1 goto END

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
