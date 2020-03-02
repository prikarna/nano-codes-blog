@rem +---------------------------------------------------------+
@rem   Batch file to build DtNuc120_GenHid_07_Rev_1 project
@rem   To run this, just type: Make <param> then press <Enter>
@rem   <param> is one of : all, clean and rebuild
@rem   If no <param> specified then the default is all
@rem +---------------------------------------------------------+

@setlocal

@set CORT_VER=m0
@set TGT_CPU=arm_cortex_%CORT_VER%
@set PROJ_NAME=DtNuc120_GenHid_07_Rev_1

@echo.
@echo *** Building %PROJ_NAME% project for DT-NUC120 microcontroller
@echo.

@set SOLUTION_DIR=D:\Microcontroller\GenHid_07_Rev_1
@set PROJ_DIR=%SOLUTION_DIR%\%PROJ_NAME%
@set BIN_DIR=%PROJ_DIR%\Bin
@set SRC_DIR=%SOLUTION_DIR%\Src\MCU
@set GCC_BIN_DIR=D:\Microcontroller\gcc-arm\bin

@set MAKE_REBUILD=0
@set MAKE_PARM="%1"

@if /I %MAKE_PARM%=="clean" goto CLEAN
@if /I %MAKE_PARM%=="rebuild" goto REBUILD
@if /I %MAKE_PARM%=="all" goto ALL
@if /I %MAKE_PARM%=="" goto ALL

@echo Unknown param %MAKE_PARM%, exiting...
@goto END


@rem +------------------------------------------------------+
@rem   Make all
@rem +------------------------------------------------------+

:ALL

@set TGT=%PROJ_NAME%.bin
@set ELF=%PROJ_NAME%.elf

@path=%path%;%GCC_BIN_DIR%

@set SRCS=%SRC_DIR%\GenHid\Init.c
@set SRCS=%SRCS% %SRC_DIR%\DkSys\DkHalUart.c
@set SRCS=%SRCS% %SRC_DIR%\DkSys\DkHalMem.c
@set SRCS=%SRCS% %SRC_DIR%\DkSys\DkHalClk.c
@set SRCS=%SRCS% %SRC_DIR%\GenHid\IntHandlers.c
@set SRCS=%SRCS% %SRC_DIR%\GenHid\UsbSetup.c
@set SRCS=%SRCS% %SRC_DIR%\GenHid\UsbEpReg0.c
@set SRCS=%SRCS% %SRC_DIR%\GenHid\UsbEpReg1.c
@set SRCS=%SRCS% %SRC_DIR%\GenHid\UsbEpReg2.c
@set SRCS=%SRCS% %SRC_DIR%\GenHid\UsbDescs.c

@set CC=arm-none-eabi-gcc.exe

@set CC_LNK_OPTS=-Wall -D_DEBUG -g -O0
@set CC_LNK_OPTS=%CC_LNK_OPTS% -D_CHIP_NUC1XX
@set CC_LNK_OPTS=%CC_LNK_OPTS% -mcpu=cortex-%CORT_VER% -mthumb
@set CC_LNK_OPTS=%CC_LNK_OPTS% -ffunction-sections
@set CC_LNK_OPTS=%CC_LNK_OPTS% -isystem%SRC_DIR%\DkSys
@set CC_LNK_OPTS=%CC_LNK_OPTS% -Wl,-Map=%BIN_DIR%\%PROJ_NAME%.map
@set CC_LNK_OPTS=%CC_LNK_OPTS% -Wl,--gc-sections
@set CC_LNK_OPTS=%CC_LNK_OPTS% -Wl,-L%PROJ_DIR%
@set CC_LNK_OPTS=%CC_LNK_OPTS% -Wl,-T%PROJ_DIR%\%PROJ_NAME%.ld
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
