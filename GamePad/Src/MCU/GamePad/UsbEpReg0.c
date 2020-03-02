#include "GamePad.h"

#ifdef _CHIP_NUC1XX

extern PUSB_SETUP		gpStp;

#elif defined _CHIP_STM32F10XXXXX

extern PUSB_SETUP_16	gpStp;
extern uint32_ptr_t		gpEp0Buf;
extern const uint8_t	gGamePadRepDesc[34];

#else
# error No chipset defined!!!
#endif

extern const int8_ptr_t		gpStrRep;

void On_EpReg0_Std_SetAddr()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	USB_SET_FUNC_ADDR(gpStp->wValue);

#elif defined _CHIP_STM32F10XXXXX

	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_IN_END);

	USB_SET_DEV_ADDR(gpStp->wValue);

#else
# error No chipset defined!!!
#endif
}

void On_EpReg0_Std_GetDesc_Dev()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG1, 0);

#elif defined _CHIP_STM32F10XXXXX

	if (((uint8_t) USB_GET_TRANSACT_DIR()) == 0) {
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_IN_OUT);
	} else {
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_OUT_END);
	}

#else
# error No chipset defined!!!
#endif
}

void On_EpReg0_Std_GetDesc_Config()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG1, 0);

#elif defined _CHIP_STM32F10XXXXX

	if (((uint8_t) USB_GET_TRANSACT_DIR()) == 0) {
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_IN_OUT);
	} else {
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_OUT_END);
	}

#else
# error No chipset defined!!!
#endif
}

void On_EpReg0_Std_GetDesc_String()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG1, 0);

#elif _CHIP_STM32F10XXXXX

	if (((uint8_t) USB_GET_TRANSACT_DIR()) == 0) {
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_IN_OUT);
	} else {
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_OUT_END);
	}

#else
# error No chipset defined!!!
#endif
}

void On_EpReg0_Std_GetDesc_Hid_Report()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG1, 0);

#elif defined _CHIP_STM32F10XXXXX

	//DBG_PRINTF("%s(): Dir=%d, Ep0=0x%h\r\n", __FUNCTION__, USB_GET_TRANSACT_DIR(), IO_MMAP(USB_EP_REG_ADDR(USB_EP_REG_0)));

	if (((uint8_t) USB_GET_TRANSACT_DIR()) == 0) {
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_IN_OUT);
	} else {
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_OUT_END);
	}

#else
# error No chipset defined!!!
#endif
}

void On_EpReg0_Std_SetConfig()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX
	// Do nothing
#elif defined _CHIP_STM32F10XXXXX
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_IN_END);
#else
# error No chipset defined!!!
#endif
}

void On_EpReg0_Cls_Hid_SetIdle()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX
	// Do nothing
#elif defined _CHIP_STM32F10XXXXX
	//DBG_PRINTF("%s(): Dir=%d, Ep0=0x%X\r\n", __FUNCTION__, USB_GET_TRANSACT_DIR(), IO_MMAP(USB_EP_REG_ADDR(USB_EP_REG_0)));
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_IN_END);
#else
# error No chipset defined!!!
#endif
}
