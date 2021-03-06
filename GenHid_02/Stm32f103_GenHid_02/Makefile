#
# Makefile for ARM Cortex-M processor based MCU
#

CORT_VER			= m3
TGT_CPU				= arm_cortex_$(CORT_VER)
PROJ_NAME			= Stm32f103_GenHid_02

SOLUTION_DIR		= D:\Microcontroller\GenHid_02
PROJ_DIR			= $(SOLUTION_DIR)\$(PROJ_NAME)
GCC_BIN_DIR			= D:\Microcontroller\gcc-arm\bin

TGT					= $(PROJ_NAME).bin
ELF					= $(PROJ_NAME).elf

SRCS				= \
					  $(SOLUTION_DIR)\DkSys\DkHalMem.c\
					  $(SOLUTION_DIR)\DkSys\DkHalClk.c\
					  $(SOLUTION_DIR)\DkSys\DkHalUart.c\
					  $(SOLUTION_DIR)\Src\IntHandlers.c\
					  $(SOLUTION_DIR)\Src\UsbSetup.c\
					  $(SOLUTION_DIR)\Src\UsbEpReg0.c\
					  $(SOLUTION_DIR)\Src\UsbEpReg1.c\
					  $(SOLUTION_DIR)\Src\UsbEpReg2.c\
					  $(SOLUTION_DIR)\Src\Init.c

PATH				= $(GCC_BIN_DIR);$(PATH)

CC					= arm-none-eabi-gcc.exe
					  
CC_LNK_OPTS			= \
					  -D_CHIP_STM32F10XXXXX\
!IFDEF _DEBUG
					  -Wall\
					  -D_DEBUG\
					  -g\
!ENDIF
					  -mcpu=cortex-$(CORT_VER)\
					  -mthumb\
					  -ffunction-sections\
					  -isystem $(SOLUTION_DIR)\DkSys\
					  -O0\
!IFDEF _DEBUG
					  -Wl,-Map=$(PROJ_DIR)\Bin\$(PROJ_NAME).map\
!ENDIF
					  -Wl,--gc-sections\
					  -Wl,-L$(PROJ_DIR)\
					  -Wl,-T$(PROJ_DIR)\$(PROJ_NAME).ld\
					  -Wl,-o$(PROJ_DIR)\Bin\$(ELF)

GEN_BIN				= arm-none-eabi-objcopy.exe
GEN_BIN_OPT			= -Obinary

all			: $(TGT)

prep		:
	@echo Preparing...
	@if not exist "$(PROJ_DIR)\Bin" mkdir "$(PROJ_DIR)\Bin"

$(ELF)		: prep
	@echo Compiling and linking...
	@$(CC) $(CC_LNK_OPTS) $(SRCS)

$(TGT)		: $(ELF)
	@echo Generating binary...
	@$(GEN_BIN) $(GEN_BIN_OPT) $(PROJ_DIR)\Bin\$(ELF) $(PROJ_DIR)\Bin\$(TGT)

clean		:
	@echo Cleaning up...
	@if exist "$(PROJ_DIR)\Bin" erase /S /Q "$(PROJ_DIR)\Bin\*.*"

rebuild		: clean all
