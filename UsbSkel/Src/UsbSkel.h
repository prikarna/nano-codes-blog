#ifndef _USBSKEL_H
#define _USBSKEL_H

#include "DkSys.h"
#include "Usb\UsbHdr.h"
#include "Usb\HidHdr.h"

uint32_t ClkGetSysClk();
uint32_t ClkSetSysClkToMaxSpeed();

void MemCopy(uint8_ptr_t pDst, uint8_ptr_t pSrc, uint32_t uLen);
void MemCopy16(uint32_ptr_t pBuf, uint16_ptr_t pSrc, uint32_t uSrcLen);
void MemSet(uint8_ptr_t pMem, uint8_t uSet, uint32_t uLen);

void UaInit();
void UaPrintf(const char *szFmt, ...);

void Spin(uint32_t uTimes);

#ifdef _DEBUG
# define DBG_INIT()						UaInit()
# define DBG_PRINTF(szFmt, ...)			UaPrintf(szFmt, __VA_ARGS__)
#else
# define DBG_INIT()
# define DBG_PRINTF(szFmt, ...)
#endif

#ifdef _CHIP_NUC1XX

# define STACK_ADDRESS		((0x20000000 + 0x00000200) - 1)
# define TGT_CHIP_STR		"DT-NUC1XX"

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

#define PROG_NAME_STR		"USB Skeleton (UsbSkel)"
#define PROG_VER_STR		"1.0.1"
#define PROG_VER			0x0101

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
void On_EpReg3Int();
void On_EpReg4Int();
void On_EpReg5Int();

void On_Stp_StdReq();
void On_Stp_ClsReq();
void On_Stp_VendReq();
void On_Stp_RsvdReq();

void On_EpReg0_StdReq();
void On_EpReg0_ClsReq();
void On_EpReg0_VendReq();
void On_EpReg0_RsvdReq();

void On_EpReg1_StdReq();
void On_EpReg1_ClsReq();
void On_EpReg1_VendReq();
void On_EpReg1_RsvdReq();

#endif   // End of _USBSKEL_H
