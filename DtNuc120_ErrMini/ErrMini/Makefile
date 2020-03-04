#
# Manual build for ARM processor based device
#

CORT_VER			= m0
TGT_CPU				= arm_cortex_$(CORT_VER)
PROJ_NAME			= ErrMini

!MESSAGE ****Build for $(TGT_CPU) based device program ($(PROJ_NAME).bin)

SOLUTION_DIR		= D:\Microcontroller\DtNuc120_ErrMini
PROJ_DIR			= $(SOLUTION_DIR)\$(PROJ_NAME)
GCC_BIN_DIR			= D:\Microcontroller\gcc-arm\bin

TGT					= $(PROJ_NAME).bin
ELF					= $(PROJ_NAME).elf

SRCS				= \
					  $(PROJ_DIR)\CMSIS.c\
					  $(PROJ_DIR)\Main.c

PATH				= $(GCC_BIN_DIR);$(PATH)

CC					= arm-none-eabi-gcc.exe
					  
CC_LNK_OPTS			= \
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
					  -Wl,-T$(PROJ_DIR)\AltMini.ld\
					  -Wl,-o$(PROJ_DIR)\Bin\$(ELF)

GEN_BIN				= arm-none-eabi-objcopy.exe
GEN_BIN_OPT			= -Obinary

all			: $(TGT)

prep		:
	@echo Preparing...
	@if not exist "$(PROJ_DIR)\Bin" mkdir "$(PROJ_DIR)\Bin"

$(ELF)		: prep
	@echo Compiling and linking...
	$(CC) $(CC_LNK_OPTS) $(SRCS)

$(TGT)		: $(ELF)
	@echo Generating binary...
	$(GEN_BIN) $(GEN_BIN_OPT) $(PROJ_DIR)\Bin\$(ELF) $(PROJ_DIR)\Bin\$(TGT)

clean		:
	@echo Cleaning up...
	@if exist "$(PROJ_DIR)\Bin" erase /S /Q "$(PROJ_DIR)\Bin\*.*"

rebuild		: clean all
