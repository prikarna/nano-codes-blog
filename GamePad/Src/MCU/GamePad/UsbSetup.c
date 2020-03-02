#include "GamePad.h"

#ifdef _CHIP_NUC1XX

extern PUSB_SETUP		gpStp;
uint8_ptr_t				gpEp0Buf = (uint8_ptr_t) (USB_SRAM + EP0_BUF_SEG);

#elif defined _CHIP_STM32F10XXXXX

extern PUSB_SETUP_16	gpStp;
uint32_ptr_t			gpEp0Buf = 0;

#else
# error No chipset defined!!!
#endif

extern const uint8_t	gDevDesc[];
extern const uint8_t	gCfgDesc[];
extern const uint8_t	gLangId[];
extern const uint8_t	gMfcStr[];
extern const uint8_t	gProdStr[];
extern const uint8_t	gSerStr[];
extern const uint8_t	gGamePadRepDesc[29];

void DefaultHandler_Stall()
{
	uint8_t		uDir = (uint8_t) ((gpStp->bmRequestType >> 7) & 0x1);
#ifdef _CHIP_NUC1XX

	if (uDir == 1) {
		USB_EP_SET_STALL(USB_EP_REG0);
		USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, 0);
	} else {
		USB_EP_SET_STALL(USB_EP_REG1);
		USB_EP_SET_MAX_PAYLOAD(USB_EP_REG1, 0);
	}

#elif defined _CHIP_STM32F10XXXXX

	if (uDir == 1) {
		USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, 0);
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_SETUP_IN_STALL);
	} else {
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_SETUP_OUT_STALL);
	}

#else
# error No chipset defined!!!
#endif
}

void On_Stp_Std_SetAddr()
{
	DBG_PRINTF("%s(): wValue = 0x%h\r\n", __FUNCTION__, gpStp->wValue);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	USB_EP_SET_DSQ_SYNC(USB_EP_REG0, SET);
	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, 0);

#elif _CHIP_STM32F10XXXXX

	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, 0);
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_SETUP_IN);

#else
# error No chipset defined!!!
#endif
}

void On_Stp_Std_GetDesc_Dev()
{
	DBG_PRINTF("%s(): wLength = 0x%h\r\n", __FUNCTION__, gpStp->wLength);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	MemCopy(gpEp0Buf, (uint8_ptr_t) &gDevDesc[0], (uint32_t) gpStp->wLength);

	USB_EP_SET_DSQ_SYNC(USB_EP_REG0, SET);
	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, ((uint32_t) gpStp->wLength));

#elif defined _CHIP_STM32F10XXXXX

	gpEp0Buf = (uint32_ptr_t) USB_EP_GET_TX_BUF_ADDR(USB_EP_REG_0, 0);
	MemCopyToPaddedBuffer(gpEp0Buf, (uint16_ptr_t) &gDevDesc[0], sizeof(USB_DEVICE_DESCRIPTOR));

	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, sizeof(USB_DEVICE_DESCRIPTOR));
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_SETUP_IN);

#else
# error No chipset defined!!!
#endif
}

void On_Stp_Std_GetDesc_Config()
{
	uint32_t							uLen, uMax;
	PUSB_CONFIGURATION_DESCRIPTOR	pCfg;

	DBG_PRINTF("%s(): wLength = 0x%h\r\n", __FUNCTION__, gpStp->wLength);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX
	uMax = EP_MAX_PLD;
#elif defined _CHIP_STM32F10XXXXX
	uMax = EP_MAX_LEN;
#else
# error No chipset defined!!!
#endif

	if (gpStp->wLength <= (uint16_t) uMax)
	{
		uLen = gpStp->wLength;
	}
	else if (gpStp->wLength == 0xFF)
	{
		pCfg = (PUSB_CONFIGURATION_DESCRIPTOR) &gCfgDesc[0];
		uLen = pCfg->wTotalLength;
	}
	else
	{
		uLen = 0;
	}

#ifdef _CHIP_NUC1XX

	if (uLen == 0) {
		USB_EP_SET_STALL(USB_EP_REG0);
		USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, 0);
		return;
	}

	MemCopy(gpEp0Buf, (uint8_ptr_t) &gCfgDesc[0], uLen);

	USB_EP_SET_DSQ_SYNC(USB_EP_REG0, SET);
	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, uLen);

#elif defined _CHIP_STM32F10XXXXX

	if (uLen == 0) {
		USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, 0);
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_SETUP_IN_STALL);
		return;
	}

	gpEp0Buf = (uint32_ptr_t) USB_EP_GET_TX_BUF_ADDR(USB_EP_REG_0, 0);
	MemCopyToPaddedBuffer(gpEp0Buf, (uint16_ptr_t) &gCfgDesc[0], uLen);

	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, uLen);
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_SETUP_IN);

#else
# error No chipset defined!!!
#endif
}

void On_Stp_Std_GetDesc_String()
{
	uint8_ptr_t	pStr = 0;
	uint32_t	uStrIdx = gpStp->wValue & 0xFF;
	uint32_t	uLen = 0;

	DBG_PRINTF("%s(): wValue = 0x%h\r\n", __FUNCTION__, gpStp->wValue);
	//DBG_BREAK();

	switch (uStrIdx)
	{
	case 0:
		pStr = (uint8_ptr_t) &gLangId[0];
		uLen = (uint32_t) gLangId[0];
		break;

	case 1:
		pStr = (uint8_ptr_t) &gMfcStr[0];
		uLen = (uint32_t) gMfcStr[0];
		break;

	case 2:
		pStr = (uint8_ptr_t) &gProdStr[0];
		uLen = (uint32_t) gProdStr[0];
		break;

	case 3:
		pStr = (uint8_ptr_t) &gSerStr[0];
		uLen = (uint32_t) gSerStr[0];
		break;

	default:
		uLen = 0;
		break;
	}

#ifdef _CHIP_NUC1XX

	if (uLen == 0) {
		USB_EP_SET_STALL(USB_EP_REG0);
		USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, 0);
		return;
	}

	MemCopy(gpEp0Buf, pStr, uLen);

	USB_EP_SET_DSQ_SYNC(USB_EP_REG0, SET);
	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, uLen);

#elif defined _CHIP_STM32F10XXXXX

	if (uLen == 0) {
		USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, 0);
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_SETUP_IN_STALL);
		return;
	}

	gpEp0Buf = (uint32_ptr_t) USB_EP_GET_TX_BUF_ADDR(USB_EP_REG_0, 0);
	MemCopyToPaddedBuffer(gpEp0Buf, (uint16_ptr_t) pStr, uLen);

	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, uLen);
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_SETUP_IN);

#else
# error No chipset defined!!!
#endif
}

void On_Stp_Std_GetDesc_Hid_Report()
{
	DBG_PRINTF("%s(): wLength=0x%h\r\n", __FUNCTION__, gpStp->wLength);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	MemCopy(gpEp0Buf, (uint8_ptr_t) &gGamePadRepDesc, sizeof(gGamePadRepDesc));

	USB_EP_SET_DSQ_SYNC(USB_EP_REG0, SET);
	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, sizeof(gGamePadRepDesc));

#elif defined _CHIP_STM32F10XXXXX

	//DBG_PRINTF("%s(): Dir=%d, Ep0=0x%h, bmReqType=0x%b, bRequest=0x%b, wValue=0x%h, wIndex=0x%h, wLength=0x%h, sizeof(gGamePadRepDesc)=%d\r\n", __FUNCTION__, USB_GET_TRANSACT_DIR(), IO_MMAP(USB_EP_REG_ADDR(USB_EP_REG_0)), gpStp->bmRequestType, gpStp->bRequest, gpStp->wValue, gpStp->wIndex, gpStp->wLength, sizeof(gGamePadRepDesc));

	gpEp0Buf = (uint32_ptr_t) USB_EP_GET_TX_BUF_ADDR(USB_EP_REG_0, 0);
	MemCopyToPaddedBuffer(gpEp0Buf, (uint16_ptr_t) &gGamePadRepDesc[0], sizeof(gGamePadRepDesc));

	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, sizeof(gGamePadRepDesc));
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_SETUP_IN);

#else
# error No chipset defined!!!
#endif
}

void On_Stp_Std_SetConfig()
{
	DBG_PRINTF("%s(): wValue = 0x%h\r\n", __FUNCTION__, gpStp->wValue);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	USB_EP_SET_DSQ_SYNC(USB_EP_REG0, SET);
	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, 0);

#elif _CHIP_STM32F10XXXXX

	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, 0);
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_SETUP_IN);

#else
# error No chipset defined!!!
#endif
}

void On_Stp_Cls_Hid_SetIdle()
{
	DBG_PRINTF("%s(): wValue=0x%h\r\n", __FUNCTION__, gpStp->wValue);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	USB_EP_SET_DSQ_SYNC(USB_EP_REG0, SET);
	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, 0);

#elif defined _CHIP_STM32F10XXXXX

	//DBG_PRINTF("%s(): Ep0=0x%X\r\n", __FUNCTION__, IO_MMAP(USB_EP_REG_ADDR(USB_EP_REG_0)));

	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_CTRL_TRANS_SETUP_IN);

#else
# error No chipset defined!!!
#endif
}
