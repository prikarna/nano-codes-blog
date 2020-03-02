#
# Makefile for Generic_Hid_07_Rev_1 application
#

PROJ_NAME			= App_GenHid_07_Rev_1

ROOT_DIR			= /home/deka/Microcontroller/GenHid_07_Rev_1
SRCS_DIR			= $(ROOT_DIR)/Src/App
PROJ_DIR			= $(ROOT_DIR)/$(PROJ_NAME)
BIN_DIR				= $(PROJ_DIR)/Bin
USB_LIB				= /lib/x86_64-linux-gnu/libusb-1.0.so.0

TGT					= $(PROJ_NAME)

SRCS				= \
					  $(SRCS_DIR)/DkHID.cpp\
					  $(SRCS_DIR)/AppGenHid.cpp

CPP					= g++
					  
CPP_LNK_OPTS		= \
					  -DLINUX_GNU\
					  -Wall\
					  -D_DEBUG\
					  -g\
					  -isystem $(PROJ_DIR)\
					  -isystem /usr/local/include\
					  -o $(BIN_DIR)/$(PROJ_NAME)

all			: $(TGT)

prep		:
	echo Preparing...
	mkdir -p $(PROJ_DIR)/Bin

$(TGT)		: prep
	echo Compiling and linking...
	$(CPP) $(CPP_LNK_OPTS) $(SRCS) $(USB_LIB)

clean		:
	echo Cleaning up...
	rm -rf $(BIN_DIR)/*

rebuild		: clean all

