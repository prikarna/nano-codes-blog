#include "UsbSkel.h"

#ifdef _CHIP_NUC1XX

extern PUSB_SETUP		gpStp;

#elif defined _CHIP_STM32F10XXXXX

extern PUSB_SETUP_16	gpStp;

#else
# error No chipset defined!!!
#endif

void On_EpReg0_Std_GetStat()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Std_ClrFeat()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Std_SetFeat()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Std_SetAddr()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	USB_SET_FUNC_ADDR(gpStp->wValue);

#elif defined _CHIP_STM32F10XXXXX

	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_IN_ACK_CTRL_TRANS);

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
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_IN_ACK_CTRL_TRANS);
	} else {
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_OUT_ACK_CTRL_TRANS);
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
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_IN_ACK_CTRL_TRANS);
	} else {
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_OUT_ACK_CTRL_TRANS);
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
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_IN_ACK_CTRL_TRANS);
	} else {
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_OUT_ACK_CTRL_TRANS);
	}

#else
# error No chipset defined!!!
#endif
}

void On_EpReg0_Std_GetDesc_Intf()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Std_GetDesc_EndPoint()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Std_GetDesc_DevQlfy()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();
}

void On_EpReg0_Std_GetDesc_OthSpeedCfg()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Std_GetDesc_IntfPwr()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Std_GetDesc_Otg()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Std_GetDesc_Debug()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Std_GetDesc_IntfAssoc()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Std_GetDesc_Hid_Phys()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Std_GetDesc_Hid_Report()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX

	USB_EP_SET_MAX_PAYLOAD(USB_EP_REG1, 0);

#elif defined _CHIP_STM32F10XXXXX

	//DBG_PRINTF("%s(): Dir=%d, Ep0=0x%X\r\n", __FUNCTION__, USB_GET_TRANSACT_DIR(), IO_MMAP(USB_EP_REG_ADDR(USB_EP_REG_0)));

	if (((uint8_t) USB_GET_TRANSACT_DIR()) == 0) {
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_IN_ACK_CTRL_TRANS);
	} else {
		USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_OUT_ACK_CTRL_TRANS);
	}

#else
# error No chipset defined!!!
#endif
}

void On_EpReg0_Std_GetDesc()
{
	uint8_t uDescType = (uint8_t) ((gpStp->wValue >> 8) & 0xFF);

	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

	switch (uDescType)
	{
	case DESCTYPE_DEVICE:
		On_EpReg0_Std_GetDesc_Dev();
		break;

	case DESCTYPE_CONFIGURATION:
		On_EpReg0_Std_GetDesc_Config();
		break;

	case DESCTYPE_STRING:
		On_EpReg0_Std_GetDesc_String();
		break;

	case DESCTYPE_INTERFACE:
		On_EpReg0_Std_GetDesc_Intf();
		break;

	case DESCTYPE_ENDPOINT:
		On_EpReg0_Std_GetDesc_EndPoint();
		break;

	case DESCTYPE_DEVICE_QUALIFIER:
		On_EpReg0_Std_GetDesc_DevQlfy();
		break;

	case DESCTYPE_OTHER_SPEED_CONFIGURATION:
		On_EpReg0_Std_GetDesc_OthSpeedCfg();
		break;

	case DESCTYPE_INTERFACE_POWER:
		On_EpReg0_Std_GetDesc_IntfPwr();
		break;

	case DESCTYPE_OTG:
		On_EpReg0_Std_GetDesc_Otg();
		break;

	case DESCTYPE_DEBUG:
		On_EpReg0_Std_GetDesc_Debug();
		break;

	case DESCTYPE_INTERFACE_ASSOCIATION:
		On_EpReg0_Std_GetDesc_IntfAssoc();
		break;

	case DESCTYPE_HID_PHYSICAL:
		On_EpReg0_Std_GetDesc_Hid_Phys();
		break;

	case DESCTYPE_HID_REPORT:
		On_EpReg0_Std_GetDesc_Hid_Report();
		break;

	default:
		DBG_PRINTF("%s(): Unknown USB descriptor type (0x%b)\r\n", __FUNCTION__, uDescType);
		DBG_BREAK();
		break;
	}
}

void On_EpReg0_Std_SetDesc()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Std_GetConfig()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Std_SetConfig()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX
	// Do nothing
#elif defined _CHIP_STM32F10XXXXX
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_IN_ACK_CTRL_TRANS);
#else
# error No chipset defined!!!
#endif
}

void On_EpReg0_Std_GetIntf()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Std_SetIntf()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Std_SyncFrame()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_StdReq()
{
	DBG_PRINTF("%s(): bRequest = 0x%b\r\n", __FUNCTION__, gpStp->bRequest);
	//DBG_BREAK();

	switch (gpStp->bRequest)
	{
	case STDREQ_GET_STATUS:
		On_EpReg0_Std_GetStat();
		break;

	case STDREQ_CLEAR_FEATURE:
		On_EpReg0_Std_ClrFeat();
		break;

	case STDREQ_SET_FEATURE:
		On_EpReg0_Std_SetFeat();
		break;

	case STDREQ_SET_ADDRESS:
		On_EpReg0_Std_SetAddr();
		break;

	case STDREQ_GET_DESCRIPTOR:
		On_EpReg0_Std_GetDesc();
		break;

	case STDREQ_SET_DESCRIPTOR:
		On_EpReg0_Std_SetDesc();
		break;

	case STDREQ_GET_CONFIGURATION:
		On_EpReg0_Std_GetConfig();
		break;

	case STDREQ_SET_CONFIGURATION:
		On_EpReg0_Std_SetConfig();
		break;

	case STDREQ_GET_INTERFACE:
		On_EpReg0_Std_GetIntf();
		break;

	case STDREQ_SET_INTERFACE:
		On_EpReg0_Std_SetIntf();
		break;

	case STDREQ_SYNCH_FRAME:
		On_EpReg0_Std_SyncFrame();
		break;

	default:
		DBG_PRINTF("%s(): Unknown USB standard setup request type (0x%b)\r\n", __FUNCTION__, gpStp->bRequest);
		DBG_BREAK();
		break;
	}
}

void On_EpReg0_Cls_Hid_GetReport()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Cls_Hid_GetIdle()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Cls_Hid_GetProt()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Cls_Hid_SetReport()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_Cls_Hid_SetIdle()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

#ifdef _CHIP_NUC1XX
	// Do nothing
#elif defined _CHIP_STM32F10XXXXX
	//DBG_PRINTF("%s(): Dir=%d, Ep0=0x%X\r\n", __FUNCTION__, USB_GET_TRANSACT_DIR(), IO_MMAP(USB_EP_REG_ADDR(USB_EP_REG_0)));
	USB_EP_CTL(USB_EP_REG_0, USB_EP_CTL_IN_ACK_CTRL_TRANS);
#else
# error No chipset defined!!!
#endif
}

void On_EpReg0_Cls_Hid_SetProt()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_ClsReq()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	//DBG_BREAK();

	switch (gpStp->bRequest)
	{
	case REQTYPE_HID_GET_REPORT:
		On_EpReg0_Cls_Hid_GetReport();
		break;

	case REQTYPE_HID_GET_IDLE:
		On_EpReg0_Cls_Hid_GetIdle();
		break;

	case REQTYPE_HID_GET_PROTOCOL:
		On_EpReg0_Cls_Hid_GetProt();
		break;

	case REQTYPE_HID_SET_REPORT:
		On_EpReg0_Cls_Hid_SetReport();
		break;

	case REQTYPE_HID_SET_IDLE:
		On_EpReg0_Cls_Hid_SetIdle();
		break;

	case REQTYPE_HID_SET_PROTOCOL:
		On_EpReg0_Cls_Hid_SetProt();
		break;

	default:
		DBG_PRINTF("%s(): Unknown setup class request type (0x%h)\r\n", __FUNCTION__, gpStp->bRequest);
		DBG_BREAK();
		break;
	}
}

void On_EpReg0_VendReq()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}

void On_EpReg0_RsvdReq()
{
	DBG_PRINTF("%s()\r\n", __FUNCTION__);
	DBG_BREAK();
}
