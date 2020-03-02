#include "UsbSkel.h"

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
extern const uint8_t	gGenRepDesc[34];

void On_Stp_Std_GetStat()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Std_ClrFeat()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Std_SetFeat()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Std_SetAddr()
{
	DBG_PRINTF("%s(): Device address = %d\r\n", __FUNCTION__, gpStp->wValue);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	USB_EP_SET_DSQ_SYNC(USB_EP_REG0, SET);
	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, 0);

#elif _CHIP_STM32F10XXXXX

	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, 0);
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_OUT_ACK_CTRL_TRANS);

#else
# error No chipset defined!!!
#endif
}

void On_Stp_Std_GetDesc_Dev()
{
	DBG_PRINTF("%s(): Setup packet length = %d\r\n", __FUNCTION__, gpStp->wLength);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	MemCopy(gpEp0Buf, (uint8_ptr_t) &gDevDesc[0], (uint32_t) gpStp->wLength);

	USB_EP_SET_DSQ_SYNC(USB_EP_REG0, SET);
	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, ((uint32_t) gpStp->wLength));

#elif defined _CHIP_STM32F10XXXXX

	gpEp0Buf = (uint32_ptr_t) USB_EP_GET_TX_BUF_ADDR(USB_EP_REG_0, 0);
	MemCopyToPaddedBuffer(gpEp0Buf, (uint16_ptr_t) &gDevDesc[0], sizeof(USB_DEVICE_DESCRIPTOR));

	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, sizeof(USB_DEVICE_DESCRIPTOR));
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_OUT_ACK_CTRL_TRANS);

#else
# error No chipset defined!!!
#endif
}

void On_Stp_Std_GetDesc_Config()
{
	uint32_t							uLen, uMax;
	PUSB_CONFIGURATION_DESCRIPTOR	pCfg;

	DBG_PRINTF("%s(): wLength = %d (0x%h)\r\n", __FUNCTION__, gpStp->wLength, gpStp->wLength);
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
		DBG_BREAK();
	}

#ifdef _CHIP_NUC1XX

	MemCopy(gpEp0Buf, (uint8_ptr_t) &gCfgDesc[0], uLen);

	USB_EP_SET_DSQ_SYNC(USB_EP_REG0, SET);
	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, uLen);

#elif defined _CHIP_STM32F10XXXXX

	gpEp0Buf = (uint32_ptr_t) USB_EP_GET_TX_BUF_ADDR(USB_EP_REG_0, 0);
	MemCopyToPaddedBuffer(gpEp0Buf, (uint16_ptr_t) &gCfgDesc[0], uLen);

	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, uLen);
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_OUT_ACK_CTRL_TRANS);

#else
# error No chipset defined!!!
#endif
}

void On_Stp_Std_GetDesc_String()
{
	uint8_ptr_t	pStr = 0;
	uint32_t	uStrIdx = gpStp->wValue & 0xFF;
	uint32_t	uLen = 0;

	DBG_PRINTF("%s(): wValue = %d (0x%h)\r\n", __FUNCTION__, gpStp->wValue, gpStp->wValue);
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
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_IN_STALL_CTRL_TRANS);
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_OUT_STALL_CTRL_TRANS);
		return;
	}

	gpEp0Buf = (uint32_ptr_t) USB_EP_GET_TX_BUF_ADDR(USB_EP_REG_0, 0);
	MemCopyToPaddedBuffer(gpEp0Buf, (uint16_ptr_t) pStr, uLen);

	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, uLen);
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_OUT_ACK_CTRL_TRANS);

#else
# error No chipset defined!!!
#endif
}

void On_Stp_Std_GetDesc_Intf()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Std_GetDesc_EndPoint()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Std_GetDesc_DevQlfy()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	USB_EP_SET_STALL(USB_EP_REG0);
	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, 0);

#elif defined _CHIP_STM32F10XXXXX

	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, 0);
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_IN_STALL_CTRL_TRANS);
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_OUT_STALL_CTRL_TRANS);

#else
# error No chipset defined!!!
#endif
}

void On_Stp_Std_GetDesc_OthSpeedCfg()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Std_GetDesc_IntfPwr()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Std_GetDesc_Otg()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Std_GetDesc_Debug()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Std_GetDesc_IntfAssoc()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Std_GetDesc_Hid_Phys()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Std_GetDesc_Hid_Report()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	MemCopy(gpEp0Buf, (uint8_ptr_t) &gGenRepDesc, sizeof(gGenRepDesc));

	USB_EP_SET_DSQ_SYNC(USB_EP_REG0, SET);
	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, sizeof(gGenRepDesc));

#elif defined _CHIP_STM32F10XXXXX

	//DBG_PRINTF("%s(): Ep0=0x%X, wLength=0x%h\r\n", __FUNCTION__, IO_MMAP(USB_EP_REG_ADDR(USB_EP_REG_0)), gpStp->wLength);

	gpEp0Buf = (uint32_ptr_t) USB_EP_GET_TX_BUF_ADDR(USB_EP_REG_0, 0);
	MemCopyToPaddedBuffer(gpEp0Buf, (uint16_ptr_t) &gGenRepDesc[0], (sizeof(gGenRepDesc)));

	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, (sizeof(gGenRepDesc)));
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_OUT_ACK_CTRL_TRANS);

#else
# error No chipset defined!!!
#endif
}

void On_Stp_Std_GetDesc()
{
	uint8_t uDescType = (uint8_t) ((gpStp->wValue >> 8) & 0xFF);

	DBG_PRINTF("%s(): wValue = %d (0x%h)\r\n", __FUNCTION__, gpStp->wValue, gpStp->wValue);

	switch (uDescType)
	{
	case DESCTYPE_DEVICE:
		On_Stp_Std_GetDesc_Dev();
		break;

	case DESCTYPE_CONFIGURATION:
		On_Stp_Std_GetDesc_Config();
		break;

	case DESCTYPE_STRING:
		On_Stp_Std_GetDesc_String();
		break;

	case DESCTYPE_INTERFACE:
		On_Stp_Std_GetDesc_Intf();
		break;

	case DESCTYPE_ENDPOINT:
		On_Stp_Std_GetDesc_EndPoint();
		break;

	case DESCTYPE_DEVICE_QUALIFIER:
		On_Stp_Std_GetDesc_DevQlfy();
		break;

	case DESCTYPE_OTHER_SPEED_CONFIGURATION:
		On_Stp_Std_GetDesc_OthSpeedCfg();
		break;

	case DESCTYPE_INTERFACE_POWER:
		On_Stp_Std_GetDesc_IntfPwr();
		break;

	case DESCTYPE_OTG:
		On_Stp_Std_GetDesc_Otg();
		break;

	case DESCTYPE_DEBUG:
		On_Stp_Std_GetDesc_Debug();
		break;

	case DESCTYPE_INTERFACE_ASSOCIATION:
		On_Stp_Std_GetDesc_IntfAssoc();
		break;

	case DESCTYPE_HID_PHYSICAL:
		On_Stp_Std_GetDesc_Hid_Phys();
		break;

	case DESCTYPE_HID_REPORT:
		On_Stp_Std_GetDesc_Hid_Report();
		break;

	default:
		DBG_PRINTF("%s(): Unknown USB descriptor type (0x%b)\r\n", __FUNCTION__, uDescType);
		DBG_BREAK();
		break;
	}
}

void On_Stp_Std_SetDesc()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Std_GetConfig()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Std_SetConfig()
{
	DBG_PRINTF("%s(): wValue = %d (0x%h)\r\n", __FUNCTION__, gpStp->wValue, gpStp->wValue);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	USB_EP_SET_DSQ_SYNC(USB_EP_REG0, SET);
	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG0, 0);

#elif _CHIP_STM32F10XXXXX

	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, 0);
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_OUT_ACK_CTRL_TRANS);

#else
# error No chipset defined!!!
#endif
}

void On_Stp_Std_GetIntf()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Std_SetIntf()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Std_SyncFrame()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_StdReq()
{
	DBG_PRINTF("%s(): bRequest = 0x%b\r\n", __FUNCTION__, gpStp->bRequest);

	switch (gpStp->bRequest)
	{
	case STDREQ_GET_STATUS:
		On_Stp_Std_GetStat();
		break;

	case STDREQ_CLEAR_FEATURE:
		On_Stp_Std_ClrFeat();
		break;

	case STDREQ_SET_FEATURE:
		On_Stp_Std_SetFeat();
		break;

	case STDREQ_SET_ADDRESS:
		On_Stp_Std_SetAddr();
		break;

	case STDREQ_GET_DESCRIPTOR:
		On_Stp_Std_GetDesc();
		break;

	case STDREQ_SET_DESCRIPTOR:
		On_Stp_Std_SetDesc();
		break;

	case STDREQ_GET_CONFIGURATION:
		On_Stp_Std_GetConfig();
		break;

	case STDREQ_SET_CONFIGURATION:
		On_Stp_Std_SetConfig();
		break;

	case STDREQ_GET_INTERFACE:
		On_Stp_Std_GetIntf();
		break;

	case STDREQ_SET_INTERFACE:
		On_Stp_Std_SetIntf();
		break;

	case STDREQ_SYNCH_FRAME:
		On_Stp_Std_SyncFrame();
		break;

	default:
		DBG_PRINTF("%s(): Unknown USB standard setup request type (0x%b)\r\n", __FUNCTION__, gpStp->bRequest);
		DBG_BREAK();
		break;
	}
}

void On_Stp_Cls_Hid_GetReport()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Cls_Hid_GetIdle()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Cls_Hid_GetProt()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_Cls_Hid_SetReport()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
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

	USB_EP_SET_TX_BUF_LEN(USB_EP_REG_0, 0, 0);
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_OUT_ACK_CTRL_TRANS);

#else
# error No chipset defined!!!
#endif
}

void On_Stp_Cls_Hid_SetProt()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_ClsReq()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

	switch (gpStp->bRequest)
	{
	case REQTYPE_HID_GET_REPORT:
		On_Stp_Cls_Hid_GetReport();
		break;

	case REQTYPE_HID_GET_IDLE:
		On_Stp_Cls_Hid_GetIdle();
		break;

	case REQTYPE_HID_GET_PROTOCOL:
		On_Stp_Cls_Hid_GetProt();
		break;

	case REQTYPE_HID_SET_REPORT:
		On_Stp_Cls_Hid_SetReport();
		break;

	case REQTYPE_HID_SET_IDLE:
		On_Stp_Cls_Hid_SetIdle();
		break;

	case REQTYPE_HID_SET_PROTOCOL:
		On_Stp_Cls_Hid_SetProt();
		break;

	default:
		DBG_PRINTF("%s(): Unknown setup class request type (0x%h)\r\n", __FUNCTION__, gpStp->bRequest);
		DBG_BREAK();
		break;
	}
}

void On_Stp_VendReq()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_Stp_RsvdReq()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}
