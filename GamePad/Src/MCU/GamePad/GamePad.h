#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "DkSys.h"
#include "Usb\UsbHdr.h"
#include "Usb\HidHdr.h"

#define USB_STD_CLEAR_FEATURE				0x0000
#define USB_STD_CLEAR_FEATURE_INTERFACE		0x0101
#define USB_STD_CLEAR_FEATURE_ENDPOINT		0x0201
#define USB_STD_GET_CONFIGURATION			0x8008
#define USB_STD_GET_DESCRIPTOR				0x8006
#define USB_STD_GET_DESCRIPTOR_INTERFACE	0x8106
#define USB_STD_GET_DESCRIPTOR_ENDPOINT		0x8206
#define USB_STD_GET_INTERFACE				0x810A
#define USB_STD_GET_STATUS					0x8000
#define USB_STD_GET_STATUS_INTERFACE		0x8100
#define USB_STD_GET_STATUS_ENDPOINT			0x8200
#define USB_STD_SET_ADDRESS					0x0005
#define USB_STD_SET_CONFIGURATION			0x0009
#define USB_STD_SET_DESCRIPTOR				0x0007
#define USB_STD_SET_FEATURE					0x0003
#define USB_STD_SET_FEATURE_INTERFACE		0x0102
#define USB_STD_SET_FEATURE_ENDPOINT		0x0203
#define USB_STD_SET_INTERFACE				0x010B
#define USB_STD_SYNC_FRAME					0x820C

#define USB_HID_GET_REPORT				0xA101
#define USB_HID_GET_IDLE				0xA102
#define USB_HID_GET_PROTOCOL			0xA103
#define USB_HID_SET_REPORT				0x2109
#define USB_HID_SET_IDLE				0x210A
#define USB_HID_SET_PROTOCOL			0x210B

uint32_t ClkGetSysClk();
uint32_t ClkSetSysClkToMaxSpeed();

void MemCopy(uint8_ptr_t pDst, uint8_ptr_t pSrc, uint32_t uLen);
void MemSet(uint8_ptr_t pMem, uint8_t uSet, uint32_t uLen);
void MemCopyToPaddedBuffer(uint32_ptr_t pDst, uint16_ptr_t pSrc, uint32_t uSrcLen);
void MemCopyFromPaddedBuffer(uint16_ptr_t pDst, uint32_ptr_t pSrc, uint32_t uSrcLen);

void UaInit();
void UaPrintf(const char *szFmt, ...);
void UaDumpMem(const char* szSrc, const char * szMsg, uint8_ptr_t pMemSrc, uint32_t uMemLen);

void Spin(uint32_t uTimes);

#ifdef _DEBUG
# define DBG_INIT()									UaInit()
# define DBG_PRINTF(szFmt, ...)						UaPrintf(szFmt, __VA_ARGS__)
# define DBG_DUMPMEM(szSrc, szMsg, pMem, uMemLen)	UaDumpMem(szSrc, szMsg, pMem, uMemLen)
#else
# define DBG_INIT()
# define DBG_PRINTF(szFmt, ...)
# define DBG_DUMPMEM(szSrc, szMsg, pMem, uMemLen)
#endif

#ifdef _CHIP_NUC1XX

# define STACK_ADDRESS		((0x20000000 + 0x00000200) - 1)
# define TGT_CHIP_STR		"NUC1XX"

# include "Chips\Nuc120\DkGpio.h"
# include "Chips\Nuc120\DkClockCtl.h"
# include "Chips\Nuc120\DkUsb.h"

#elif defined _CHIP_STM32F10XXXXX

# define STACK_ADDRESS		((0x20000000 + 0x00005000) - 1)
# define TGT_CHIP_STR		"STM32F103XXXX"

# include "Chips\Stm32f103\DkGpio.h"
# include "Chips\Stm32f103\DkRcc.h"
# include "Chips\Stm32f103\DkUsb.h"

#else
# error No chipset defined!!!
#endif  // End of _CHIP_XXX

#define PROG_NAME_STR		"Simple Game Pad (SimPad)"
#define PROG_VER_STR		"1.0.22"
#define PROG_VER			0x0116

void InitUsbCtrl();
void ResetHandler();

#ifdef _CHIP_NUC1XX

#define EP_MAX_PLD			0x40
#define EP0_BUF_SEG			0x08
#define EP1_BUF_SEG			(EP0_BUF_SEG + EP_MAX_PLD)
#define EP2_BUF_SEG			(EP1_BUF_SEG + EP_MAX_PLD)

void On_FloatDetInt();
void On_BusInt();

#elif defined _CHIP_STM32F10XXXXX

typedef struct _USB_SETUP_16 {
	unsigned char	bmRequestType;
	unsigned char	bRequest;
	unsigned char	Pad0;
	unsigned char	Pad1;
	unsigned short	wValue;
	unsigned char	Pad2;
	unsigned char	Pad3;
	unsigned short	wIndex;
	unsigned char	Pad4;
	unsigned char	Pad5;
	unsigned short	wLength;
	unsigned char	Pad6;
	unsigned char	Pad7;
} USB_SETUP_16, *PUSB_SETUP_16;

#define EP_MAX_LEN			0x40
#define EP0_RX_BUF_SEG		0x20
#define EP0_TX_BUF_SEG		(EP0_RX_BUF_SEG + (EP_MAX_LEN * 2))
#define EP1_TX_BUF_SEG		(EP0_TX_BUF_SEG + (EP_MAX_LEN * 2))

void On_CorrectTransInt();
void On_PackMemOvrUndRunInt();
void On_ErrorInt();
void On_StartOfFrameInt();
void On_ExpectStartOfFrameInt();
void On_SuspendInt();

#else
# error No chipset defined!!!
#endif

void On_BusReset();
void On_WakeUpInt();
void On_StpInt();

void On_EpReg0Int();
void On_EpReg1Int();
void On_EpReg2Int();

void On_Stp_Std_GetDesc_Dev();
void On_Stp_Std_GetDesc_Config();
void On_Stp_Std_GetDesc_String();
void On_Stp_Std_GetDesc_Hid_Report();
void On_Stp_Std_SetAddr();
void On_Stp_Std_SetConfig();
void On_Stp_Cls_Hid_SetIdle();

void On_EpReg0_Std_GetDesc_Dev();
void On_EpReg0_Std_GetDesc_Config();
void On_EpReg0_Std_GetDesc_String();
void On_EpReg0_Std_GetDesc_Hid_Report();
void On_EpReg0_Std_SetAddr();
void On_EpReg0_Std_SetConfig();
void On_EpReg0_Cls_Hid_SetIdle();

void On_EpReg1_Cls_Hid_SetReport();
void On_EpReg1_Default();

void DefaultHandler_Stall();

#endif   // End of GAMEPAD_H
